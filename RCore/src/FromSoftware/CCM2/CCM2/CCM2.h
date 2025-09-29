#pragma once
#include "TexRegion/TexRegion.h"
#include "Glyph/Glyph.h"

namespace FontData
{
	namespace CCM2
	{
		struct CCM2
		{
			UINT format;
			UINT fileSize;
			USHORT fontHeight;
			USHORT textureWidth;
			USHORT textureHeight;
			USHORT texRegionCount;
			UINT glyphCount;
			UINT texRegionOffset;
			UINT glyphOffset;
			BYTE bVar1C;
			bool isBigEndian;
			USHORT textureCount;

			void locate();
			CCM2 endianSwap();
		};
	}
}