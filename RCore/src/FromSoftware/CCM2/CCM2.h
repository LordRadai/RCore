#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include "TexRegion/TexRegion.h"
#include "Glyph/Glyph.h"
#include "RFile/RFile.h"

namespace CCM2
{
	class Header
	{
	public:
		UINT m_format;
		UINT m_fileSize;
		USHORT m_fontHeight;
		USHORT m_textureWidth;
		USHORT m_textureHeight;
		USHORT m_texRegionCount;
		USHORT m_glyphCount;
		USHORT m_sVar12;
		UINT m_iVar14;
		UINT m_glyphOffset;
		BYTE m_bVar1C;
		BYTE m_bVar1D;
		BYTE m_textureCount;
		BYTE m_bVar1F;

		Header();
		Header(RFile* resource);
		Header(int font_size, int texture_size, int texRegionCount, int glyphCount, int textureCount);
		~Header();

		void calculateOffsets();
		void writeToFile(RFile* pOut);
	};

	class CCM2Reader
	{
	private:
		std::wstring m_fileName;

		PWSTR m_filePath;
		UINT64 m_fileSize;
		PWSTR m_outFilePath;
		UINT64 m_outFileSize;
		bool m_init = false;

		Header m_header;
		std::vector<TexRegion> m_texRegions;
		std::vector<Glyph> m_glyphs;

	public:
		CCM2Reader();
		CCM2Reader(PWSTR pwPath);
		~CCM2Reader();

		bool getInitStatus();
		int getTexRegionCount();
		int getGlyphCount();
		TexRegion* getTexRegion(int idx);
		Glyph* getGlyph(int idx);

		void addTexRegion(TexRegion texRegion);
		void addGlyph(Glyph glyph);
		bool createCCM2(std::string pwPath, int font_size, int texture_size, int textureCount);
		bool writeFile(std::string pwPath);
	};
}