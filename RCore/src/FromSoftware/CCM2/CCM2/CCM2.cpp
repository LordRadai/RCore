#include "CCM2.h"
#include "RMemory/RMemory.h"

namespace FontDataCCM2
{
	namespace CCM2
	{
		void Glyph::locate(char* ptr) {}

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

		void CCM2::locate()
		{
		};

		CCM2 CCM2::endianSwap()
		{
			CCM2 swapped = *this;
			swapped.format = RMemory::endianSwap(format);
			swapped.fileSize = RMemory::endianSwap(fileSize);
			swapped.fontHeight = RMemory::endianSwap(fontHeight);
			swapped.textureWidth = RMemory::endianSwap(textureWidth);
			swapped.textureHeight = RMemory::endianSwap(textureHeight);
			swapped.texRegionCount = RMemory::endianSwap(texRegionCount);
			swapped.glyphCount = RMemory::endianSwap(glyphCount);
			swapped.texRegionOffset = RMemory::endianSwap(texRegionOffset);
			swapped.glyphOffset = RMemory::endianSwap(glyphOffset);
			swapped.bVar1C = bVar1C;
			swapped.isBigEndian = isBigEndian;
			swapped.textureCount = RMemory::endianSwap(textureCount);

			return swapped;
		}
	}
}