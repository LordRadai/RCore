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
			BYTE bVar1C;
			bool isBigEndian;
			BYTE textureCount;

			void locate();
			CCM2 endianSwap();
		};
	}
}