#include "CCM.h"
#include "RMemory/RMemory.h"

namespace FontDataCCM
{
	namespace CCM
	{
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
			swapped.sVarE = RMemory::endianSwap(sVarE);
			swapped.codeGroupCount = RMemory::endianSwap(codeGroupCount);
			swapped.glyphCount = RMemory::endianSwap(glyphCount);
			swapped.codeGroupOffset = RMemory::endianSwap(codeGroupOffset);
			swapped.glyphOffset = RMemory::endianSwap(glyphOffset);
			swapped.bVar1C = bVar1C;
			swapped.isBigEndian = !isBigEndian;
			swapped.textureCount = RMemory::endianSwap(textureCount);

			return swapped;
		}
	}
}
