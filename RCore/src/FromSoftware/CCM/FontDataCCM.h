#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include "CCM/CCM.h"
#include "RFile/RFile.h"

namespace FontDataCCM
{
	class CodeGroup
	{
		friend class FontDataCCM;

	public:
		static CodeGroup* create(int startCode, int endCode, int glyphIndex);
		static CodeGroup* createFromResource(CCM::CodeGroup* resource, char* ptr, bool bBigEndian);

		void destroy();

		int getStartCode() const { return this->m_startCode; }
		int getEndCode() const { return this->m_endCode; }
		int getGlyphIndex() const { return this->m_glyphIndex; }

		bool isCharCodeInRange(int charCode) const { return (charCode >= this->m_startCode && charCode <= this->m_endCode); }
		int getGlyphIndexForCharCode(int charCode) const;
	protected:
		CodeGroup() {}
		~CodeGroup() {}

		int getMemoryRequirements();
		CCM::CodeGroup generateBinary(RFile* file, bool bBigEndian);

		int m_startCode = 0;
		int m_endCode = 0;
		int m_glyphIndex = 0;
	};

	class Glyph
	{
		friend class FontDataCCM;
	public:
		static Glyph* create(float u1, float v1, float u2, float v2, short textureIdx, short preSpace, short width, short advance);
		static Glyph* createFromResource(CCM::Glyph* resource, char* ptr, bool bBigEndian);

		void destroy();

		float getU1() const { return this->m_u1; }
		float getV1() const { return this->m_v1; }
		float getU2() const { return this->m_u2; }
		float getV2() const { return this->m_v2; }
		short getPreSpace() const { return this->m_preSpace; }
		short getWidth() const { return this->m_width; }
		short getAdvance() const { return this->m_advance; }
		short getTextureIndex() const { return this->m_textureIndex; }

	protected:
		Glyph() {}
		~Glyph() {}

		int getMemoryRequirements();
		CCM::Glyph generateBinary(RFile* file, bool bBigEndian);

		float m_u1 = 0.0f;
		float m_v1 = 0.0f;
		float m_u2 = 0.0f;
		float m_v2 = 0.0f;
		int m_preSpace = 0;
		int m_width = 0;
		int m_advance = 0;
		int m_textureIndex = 0;
	};

	class FontDataCCM
	{
	public:
		static FontDataCCM* create(int font_size, int texture_size);
		static FontDataCCM* loadFile(std::wstring path);

		void destroy();

		bool getInitStatus() const { return this->m_init; }

		int getNumCodeGroups() const { return this->m_codeGroups.size(); }
		int getNumGlyphs() const { return this->m_glyphs.size(); }

		CodeGroup* getCodeGroup(int idx);
		Glyph* getGlyph(int idx);
		Glyph* getGlyphByCharCode(int charCode);

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
		FontDataCCM() {}
		~FontDataCCM() {}

		int getMemoryRequirements();
		CCM::CCM generateBinary(RFile* file, bool bBigEndian);

		std::wstring m_fileName = L"";
		std::wstring m_filePath = L"";
		size_t m_fileSize = 0;
		bool m_init = false;

		int m_format = 0;
		int m_fontHeight = 0;
		int m_textureWidth = 0;
		int m_textureHeight = 0;
		int m_numTextures = 0;
		bool m_bBigEndian = false;
		std::vector<CodeGroup*> m_codeGroups;
		std::vector<Glyph*> m_glyphs;
	};
}
