#include "CCM2.h"
#include "RMemory/RMemory.h"

namespace DLFontData
{
	namespace CCM2
	{
		void CCM2::locate()
		{
		};

		void CCM2::endianSwap()
		{
			format = RMemory::endian_swap(format);
			fileSize = RMemory::endian_swap(fileSize);
			fontHeight = RMemory::endian_swap(fontHeight);
			textureWidth = RMemory::endian_swap(textureWidth);
			textureHeight = RMemory::endian_swap(textureHeight);
			texRegionCount = RMemory::endian_swap(texRegionCount);
			glyphCount = RMemory::endian_swap(glyphCount);
			texRegionOffset = RMemory::endian_swap(texRegionOffset);
			glyphOffset = RMemory::endian_swap(glyphOffset);
			alignment = RMemory::endian_swap(alignment);
			textureCount = RMemory::endian_swap(textureCount);
		}
	}
}