#pragma once
#include <fstream>
#include "RFile/RFile.h"

namespace CCM2
{
	struct TexRegion
	{
		short x1 = 0;
		short y1 = 0;
		short x2 = 0;
		short y2 = 0;

		TexRegion() {}
		TexRegion(RFile* resource);
		TexRegion(short x1, short y1, short x2, short y2);
		~TexRegion() {}
	};
}