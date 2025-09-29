#include "Glyph.h"
#include "../TexRegion/TexRegion.h"
#include "RMemory/RMemory.h"

namespace FontDataCCM2
{
	namespace CCM2
	{
		void Glyph::locate(char* ptr)
		{
		}

		Glyph Glyph::endianSwap()
		{
			Glyph swapped = *this;
			swapped.code = RMemory::endianSwap(code);
			swapped.texRegionOffset = RMemory::endianSwap(texRegionOffset);
			swapped.textureIndex = RMemory::endianSwap(textureIndex);
			swapped.preSpace = RMemory::endianSwap(preSpace);
			swapped.width = RMemory::endianSwap(width);
			swapped.advance = RMemory::endianSwap(advance);
			swapped.iVar10 = RMemory::endianSwap(iVar10);
			swapped.iVar14 = RMemory::endianSwap(iVar14);

			return swapped;
		}
	}
}