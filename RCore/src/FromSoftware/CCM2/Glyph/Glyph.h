#pragma once
#include <fstream>
#include <Windows.h>
#include "RFile/RFile.h"

namespace CCM2
{
	class Glyph
	{
	public:
		int m_code;
		int m_texRegionOffset;
		short m_textureIndex;
		short m_preSpace;
		short m_width;
		short m_advance;
		int m_iVar10;
		int m_iVar14;

		Glyph();
		Glyph(RFile* resource);
		Glyph(WCHAR code, int idx, short textureIdx, short preSpace, short width, short advance);
		~Glyph();

		bool writeToFile(RFile* pOut);
	};
}