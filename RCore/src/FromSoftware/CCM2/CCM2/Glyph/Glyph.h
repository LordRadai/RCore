#pragma once
#include <fstream>
#include <Windows.h>
#include "RFile/RFile.h"

namespace CCM2
{
	class Glyph
	{
	public:
		int m_code = 0;
		int m_texRegionOffset = 0;
		short m_textureIndex = 0;
		short m_preSpace = 0;
		short m_width = 0;
		short m_advance = 0;
		int m_iVar10 = 0;
		int m_iVar14 = 0;

		Glyph() {}
		Glyph(RFile* resource);
		Glyph(WCHAR code, int idx, short textureIdx, short preSpace, short width, short advance);
		~Glyph() {}

		bool writeToFile(RFile* pOut);
	};
}