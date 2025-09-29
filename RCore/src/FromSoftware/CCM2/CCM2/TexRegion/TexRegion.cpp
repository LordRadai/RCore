#include "TexRegion.h"
#include "RMemory/RMemory.h"

namespace DLFontData
{
	namespace CCM2
	{
		void TexRegion::locate(char* ptr) {}

		void TexRegion::endianSwap()
		{
			x1 = RMemory::endian_swap(x1);
			y1 = RMemory::endian_swap(y1);
			x2 = RMemory::endian_swap(x2);
			y2 = RMemory::endian_swap(y2);
		}
	}
}