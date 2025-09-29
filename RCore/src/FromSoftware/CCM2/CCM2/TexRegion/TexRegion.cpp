#include "TexRegion.h"
#include "RMemory/RMemory.h"

namespace DLFontData
{
	namespace CCM2
	{
		void TexRegion::locate(char* ptr) {}

		TexRegion TexRegion::endianSwap()
		{
			TexRegion swapped = *this;
			swapped.x1 = RMemory::endian_swap(x1);
			swapped.y1 = RMemory::endian_swap(y1);
			swapped.x2 = RMemory::endian_swap(x2);
			swapped.y2 = RMemory::endian_swap(y2);

			return swapped;
		}
	}
}