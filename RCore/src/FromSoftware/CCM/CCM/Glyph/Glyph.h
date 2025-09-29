#pragma once
#include <Windows.h>

namespace FontData
{
	namespace CCM2
	{
		struct Glyph
		{
			float u1;
			float v1;
			float u2;
			float v2;
			USHORT prespace;
			USHORT width;
			USHORT advance;
			USHORT textureIndex;

			void locate(char* ptr);
			Glyph endianSwap();
		};
	}
}