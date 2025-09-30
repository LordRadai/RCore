#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include "CCM2/CCM2.h"
#include "RFile/RFile.h"

namespace FontDataCCM2
{
	class TexRegion
	{
		friend class FontDataCCM2;
		friend class Glyph;

	public:
		static TexRegion* create(short x1, short y1, short x2, short y2);
		static TexRegion* createFromResource(CCM2::TexRegion* resource);

		void destroy();

		int getX1() const { return this->m_x1; }
		int getY1() const { return this->m_y1; }
		int getX2() const { return this->m_x2; }
		int getY2() const { return this->m_y2; }

	protected:
		TexRegion() {}
		~TexRegion() {}

		int getMemoryRequirements();
		CCM2::TexRegion generateBinary(RFile* file, bool bBigEndian);

		short m_x1 = 0;
		short m_y1 = 0;
		short m_x2 = 0;
		short m_y2 = 0;
	};

	class Glyph
	{
		friend class FontDataCCM2;

	public:
		static Glyph* create(int code, int idx, short textureIdx, short preSpace, short width, short advance, TexRegion* pTexRegion);
		static Glyph* createFromResource(CCM2::Glyph* resource, char* ptr, bool bBigEndian);

		void destroy();

		int getCode() const { return this->m_code; }
		short getTextureIndex() const { return this->m_textureIndex; }
		short getPreSpace() const { return this->m_preSpace; }
		short getWidth() const { return this->m_width; }
		short getAdvance() const { return this->m_advance; }

	private:
		Glyph() {}
		~Glyph() {}

		int getMemoryRequirements();
		CCM2::Glyph generateBinary(RFile* file, int glyphIdx, bool bBigEndian);

		int m_code = 0;
		TexRegion* m_texRegion = nullptr;
		short m_textureIndex = 0;
		short m_preSpace = 0;
		short m_width = 0;
		short m_advance = 0;
	};

	class FontDataCCM2
	{
	public:
		static FontDataCCM2* create(int font_size, int texture_size);
		static FontDataCCM2* loadFile(std::wstring path);

		void destroy();

		bool getInitStatus() const { return this->m_init; }

		int getNumGlyphs() const { return this->m_glyphs.size(); }
		Glyph* getGlyph(int idx);

		int getFontHeight() const { return this->m_fontHeight; }
		int getTextureWidth() const { return this->m_textureWidth; }
		int getTextureHeight() const { return this->m_textureHeight; }
		int getNumTextures() const { return this->m_numTextures; }
		std::wstring getFileName() const { return this->m_fileName; }
		std::wstring getFilePath() const { return this->m_filePath; }
		size_t getFileSize() const { return this->m_fileSize; }

		void setNumTextures(int count) { this->m_numTextures = count; }

		void addGlyph(Glyph* glyph);

		bool save(std::wstring path, bool bBigEndian = false);

	protected:
		FontDataCCM2() {}
		~FontDataCCM2() {}

		int getMemoryRequirements();
		CCM2::CCM2 generateBinary(RFile* file, bool bBigEndian);

		std::wstring m_fileName = L"";
		std::wstring m_filePath = L"";
		size_t m_fileSize = 0;
		bool m_init = false;

		int m_fontHeight = 0;
		int m_textureWidth = 0;
		int m_textureHeight = 0;
		bool m_bBigEndian = false;
		int m_numTextures = 0;

		std::vector<Glyph*> m_glyphs;
	};
}