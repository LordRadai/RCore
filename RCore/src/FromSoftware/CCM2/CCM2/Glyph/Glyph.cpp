#include "Glyph.h"
#include "../TexRegion/TexRegion.h"
#include "RMemory/RMemory.h"

namespace DLFontData
{
	namespace CCM2
	{
		void Glyph::locate(char* ptr)
		{
		}

		Glyph Glyph::endianSwap()
		{
			Glyph swapped = *this;
			swapped.code = RMemory::endian_swap(code);
			swapped.texRegionOffset = RMemory::endian_swap(texRegionOffset);
			swapped.textureIndex = RMemory::endian_swap(textureIndex);
			swapped.preSpace = RMemory::endian_swap(preSpace);
			swapped.width = RMemory::endian_swap(width);
			swapped.advance = RMemory::endian_swap(advance);
			swapped.iVar10 = RMemory::endian_swap(iVar10);
			swapped.iVar14 = RMemory::endian_swap(iVar14);

			return swapped;
		}
	}
}