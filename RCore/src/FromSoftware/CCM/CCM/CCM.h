#pragma once
#include <Windows.h>

namespace FontDataCCM
{
	namespace CCM
	{
		struct CodeGroup
		{
			int startCode = 0;
			int endCode = 0;
			int glyphIndex = 0;

			void locate(char* ptr);
			CodeGroup endianSwap();
		};

		struct Glyph
		{
			float u1;
			float v1;
			float u2;
			float v2;
			short prespace;
			short width;
			short advance;
			short textureIndex;

			void locate(char* ptr);
			Glyph endianSwap();
		};

		struct CCM
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
			CCM endianSwap();
		};
	}
}