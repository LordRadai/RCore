#pragma once
#include <fstream>
#include "RFile/RFile.h"

namespace CCM2
{
	class TexRegion
	{
	public:
		short m_x1;
		short m_y1;
		short m_x2;
		short m_y2;

		TexRegion();
		TexRegion(RFile* resource);
		TexRegion(short x1, short y1, short x2, short y2);
		~TexRegion();

		bool writeToFile(RFile* pOut);
	};
}