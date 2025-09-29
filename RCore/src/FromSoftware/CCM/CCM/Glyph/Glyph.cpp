#include "Glyph.h"
#include "RMemory/RMemory.h"

namespace FontData
{
	namespace CCM2
	{
		void Glyph::locate(char* ptr)
		{
		}

		Glyph Glyph::endianSwap()
		{
			Glyph swapped = *this;
			swapped.u1 = RMemory::endianSwap(u1);
			swapped.v1 = RMemory::endianSwap(v1);
			swapped.u2 = RMemory::endianSwap(u2);
			swapped.v2 = RMemory::endianSwap(v2);
			swapped.prespace = RMemory::endianSwap(prespace);
			swapped.width = RMemory::endianSwap(width);
			swapped.advance = RMemory::endianSwap(advance);
			swapped.textureIndex = RMemory::endianSwap(textureIndex);

			return swapped;
		}
	}
}
