#pragma once
#include <Windows.h>

namespace FontDataCCM2
{
	namespace CCM2
	{
		struct Glyph
		{
			int code = 0;
			int texRegionOffset = 0;
			short textureIndex = 0;
			short preSpace = 0;
			short width = 0;
			short advance = 0;
			int iVar10 = 0;
			int iVar14 = 0;

			void locate(char* ptr);
			Glyph endianSwap();
		};

		struct TexRegion
		{
			short x1 = 0;
			short y1 = 0;
			short x2 = 0;
			short y2 = 0;

			void locate(char* ptr);
			TexRegion endianSwap();
		};

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