#include "CCM.h"
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
			swapped.glyphIndex = RMemory::endianSwap(glyphIndex);

			return swapped;
		}

		void Glyph::locate(char* ptr) {}

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

		void CCM::locate()
		{
		};

		CCM CCM::endianSwap()
		{
			CCM swapped = *this;
			swapped.format = RMemory::endianSwap(format);
			swapped.fileSize = RMemory::endianSwap(fileSize);
			swapped.fontHeight = RMemory::endianSwap(fontHeight);
			swapped.textureWidth = RMemory::endianSwap(textureWidth);
			swapped.textureHeight = RMemory::endianSwap(textureHeight);
			swapped.sVarE = RMemory::endianSwap(sVarE);
			swapped.codeGroupCount = RMemory::endianSwap(codeGroupCount);
			swapped.glyphCount = RMemory::endianSwap(glyphCount);
			swapped.codeGroupOffset = RMemory::endianSwap(codeGroupOffset);
			swapped.glyphOffset = RMemory::endianSwap(glyphOffset);
			swapped.bVar1C = bVar1C;
			swapped.isBigEndian = isBigEndian;
			swapped.textureCount = RMemory::endianSwap(textureCount);

			return swapped;
		}
	}
}
