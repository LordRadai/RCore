#include "PARAMDEF.h"
#include "RCore.h"

namespace Param
{
	namespace PARAMDEF
	{
		void Field::locate(bool bigEndian, char* stringBase)
		{
			if (bigEndian)
			{				
				for (int i = 0; i < 32; i++)
					editorName[i] = RMemory::endianSwap(editorName[i]);

				defaultValue = RMemory::endianSwap(defaultValue);
				minimum = RMemory::endianSwap(minimum);
				maximum = RMemory::endianSwap(maximum);
				increment = RMemory::endianSwap(increment);
				editorFlags = RMemory::endianSwap(editorFlags);
				byteCount = RMemory::endianSwap(byteCount);
				description = RMemory::endianSwap(description);
				sortID = RMemory::endianSwap(sortID);
				bonusStringA = RMemory::endianSwap(bonusStringA);
				bonusStringB = RMemory::endianSwap(bonusStringB);
				bonusStringC = RMemory::endianSwap(bonusStringC);
			}

			if (description != nullptr)
				RMemory::fixPtr(description, stringBase);

			if (bonusStringA != nullptr)
				RMemory::fixPtr(bonusStringA, stringBase);

			if (bonusStringB != nullptr)
				RMemory::fixPtr(bonusStringB, stringBase);

			if (bonusStringC != nullptr)
				RMemory::fixPtr(bonusStringC, stringBase);

			// Endian swap the read strings
			if (bigEndian)
			{
				if (description)
				{
					size_t len = wcslen(description);
					for (size_t i = 0; i < len; i++)
						description[i] = RMemory::endianSwap(description[i]);
				}

				if (bonusStringA)
				{
					size_t len = wcslen(bonusStringA);
					for (size_t i = 0; i < len; i++)
						bonusStringA[i] = RMemory::endianSwap(bonusStringA[i]);
				}

				if (bonusStringB)
				{
					size_t len = wcslen(bonusStringB);
					for (size_t i = 0; i < len; i++)
						bonusStringB[i] = RMemory::endianSwap(bonusStringB[i]);
				}

				if (bonusStringC)
				{
					size_t len = wcslen(bonusStringC);
					for (size_t i = 0; i < len; i++)
						bonusStringC[i] = RMemory::endianSwap(bonusStringC[i]);
				}
			}
		}

		void Header::locate(char* stringBase)
		{
			bool bigEndian = this->bigEndian == 0xFF;

			if (bigEndian)
			{
				fileSize = RMemory::endianSwap(fileSize);
				headerSize = RMemory::endianSwap(headerSize);
				dataVersion = RMemory::endianSwap(dataVersion);
				fieldCount = RMemory::endianSwap(fieldCount);
				fieldSize = RMemory::endianSwap(fieldSize);
				formatVersion = RMemory::endianSwap(formatVersion);
			}

			if (formatVersion != 105)
				throw std::runtime_error("Unsupported PARAMDEF format version: " + std::to_string(formatVersion));
		}

		void PARAMDEF::locate()
		{
			bool bigEndian = header.bigEndian == 0xFF;

			char* baseAddr = reinterpret_cast<char*>(this);
			header.locate(baseAddr);

			for (size_t i = 0; i < header.fieldCount; i++)
				fields[i].locate(bigEndian, baseAddr);
		}
	}
}