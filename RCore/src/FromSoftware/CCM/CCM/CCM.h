#pragma once
#include <Windows.h>
#include "CodeGroup/CodeGroup.h"
#include "Glyph/Glyph.h"

namespace FontData
{
	namespace CCM
	{
		struct CCM2
		{
			UINT format;
			UINT fileSize;
			USHORT fontHeight;
			USHORT textureWidth;
			USHORT textureHeight;
			USHORT sVarE;
			USHORT codeGroupCount;
			USHORT glyphCount;
			UINT codeGroupOffset;
			UINT glyphOffset;
			bool bVar1C;
			bool bVar1D;
			BYTE textureCount;

			void locate();
			CCM2 endianSwap();
			bool isBigEndian() { return format == 512; }
		};
	}
}