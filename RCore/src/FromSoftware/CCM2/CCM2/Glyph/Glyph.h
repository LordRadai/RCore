#pragma once
#include <fstream>
#include <Windows.h>
#include "RFile/RFile.h"

namespace CCM2
{
	class Glyph
	{
	public:
		int code = 0;
		int texRegionOffset = 0;
		short textureIndex = 0;
		short preSpace = 0;
		short width = 0;
		short advance = 0;
		int iVar10 = 0;
		int iVar14 = 0;

		void locate(char* ptr);
	};
}