#include "CCM2.h"
#include "RMemory/RMemory.h"

namespace DLFontData
{
	namespace CCM2
	{
		void CCM2::locate()
		{
		};

		CCM2 CCM2::endianSwap()
		{
			CCM2 swapped = *this;
			swapped.format = RMemory::endian_swap(format);
			swapped.fileSize = RMemory::endian_swap(fileSize);
			swapped.fontHeight = RMemory::endian_swap(fontHeight);
			swapped.textureWidth = RMemory::endian_swap(textureWidth);
			swapped.textureHeight = RMemory::endian_swap(textureHeight);
			swapped.texRegionCount = RMemory::endian_swap(texRegionCount);
			swapped.glyphCount = RMemory::endian_swap(glyphCount);
			swapped.texRegionOffset = RMemory::endian_swap(texRegionOffset);
			swapped.glyphOffset = RMemory::endian_swap(glyphOffset);
			swapped.alignment = RMemory::endian_swap(alignment);
			swapped.textureCount = RMemory::endian_swap(textureCount);
			return swapped;
		}
	}
}