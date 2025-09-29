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

		void Glyph::endianSwap()
		{
			code = RMemory::endian_swap(code);
			texRegionOffset = RMemory::endian_swap(texRegionOffset);
			textureIndex = RMemory::endian_swap(textureIndex);
			preSpace = RMemory::endian_swap(preSpace);
			width = RMemory::endian_swap(width);
			advance = RMemory::endian_swap(advance);
			iVar10 = RMemory::endian_swap(iVar10);
			iVar14 = RMemory::endian_swap(iVar14);
		}
	}
}