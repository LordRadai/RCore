#include "PARAM.h"
#include "RMemory/RMemory.h"

namespace Param
{
	namespace PARAM
	{
		template<typename T>
		void Header<T>::locate(void* ptr)
		{
			RMemory::fixPtr(&rowNames, ptr);
			RMemory::fixPtr(&pData, ptr);
		}

		template<typename T>
		void Row<T>::locate(void* ptr)
		{
			RMemory::fixPtr(&data, ptr);
			RMemory::fixPtr(&name, ptr);
		}

		template<typename T>
		void PARAM<T>::locate()
		{
			header.locate(this);
			for (uint16_t i = 0; i < header.rowCount; i++)
				rows[i].locate(this);
		}
	}
}
