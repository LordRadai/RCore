#pragma once
#include <Windows.h>

namespace FontData
{
	namespace CCM
	{
		struct CodeGroup
		{
			USHORT startCode = 0;
			USHORT endCode = 0;
			UINT glyphOffset = 0;

			void locate(char* ptr);
			CodeGroup endianSwap();
		};
	}
}
