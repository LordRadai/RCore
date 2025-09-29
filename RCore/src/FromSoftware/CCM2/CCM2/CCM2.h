#pragma once
#include "TexRegion/TexRegion.h"
#include "Glyph/Glyph.h"

namespace DLFontData
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
			USHORT glyphCount;
			BYTE pad[2];
			UINT texRegionOffset;
			UINT glyphOffset;
			USHORT alignment;
			USHORT textureCount;

			void locate();
			void endianSwap();
			bool isBigEndian() { return format == 0x20000; }
		};
	}
}