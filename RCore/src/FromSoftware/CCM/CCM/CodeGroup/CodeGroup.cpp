#include "CodeGroup.h"
#include "RMemory/RMemory.h"

namespace FontDataCCM
{
	namespace CCM
	{
		void CodeGroup::locate(char* ptr) {}

		CodeGroup CodeGroup::endianSwap()
		{
			CodeGroup swapped = *this;
			swapped.startCode = RMemory::endianSwap(startCode);
			swapped.endCode = RMemory::endianSwap(endCode);
			swapped.glyphOffset = RMemory::endianSwap(glyphOffset);

			return swapped;
		}
	}
}