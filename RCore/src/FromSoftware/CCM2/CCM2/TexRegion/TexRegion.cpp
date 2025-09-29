#include "TexRegion.h"
#include "RMemory/RMemory.h"

namespace FontDataCCM2
{
	namespace CCM2
	{
		void TexRegion::locate(char* ptr) {}

		TexRegion TexRegion::endianSwap()
		{
			TexRegion swapped = *this;
			swapped.x1 = RMemory::endianSwap(x1);
			swapped.y1 = RMemory::endianSwap(y1);
			swapped.x2 = RMemory::endianSwap(x2);
			swapped.y2 = RMemory::endianSwap(y2);

			return swapped;
		}
	}
}