#pragma once
#include <cstdint>
#define MAX_ROW_COUNT 0xFFFF

namespace Param
{
	namespace PARAM
	{
		template<typename T>
		struct Header
		{
			char* rowNames;
			uint16_t dataVersion;
			uint16_t rowCount;
			char paramType[32];
			bool isBigEndian;
			uint8_t format[2];
			uint8_t paramDefFormatVersion;
			T* pData;

			void locate(void* ptr);
		};

		template<typename T>
		struct Row
		{
			uint32_t id;
			T* data;
			char* name;

			void locate(void* ptr);
		};

		template<typename T>
		struct PARAM
		{
			Header<T> header;
			Row<T> rows[MAX_ROW_COUNT];

			void locate();
		};
	}
}