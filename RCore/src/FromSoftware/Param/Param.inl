#pragma once
#include <vector>
#include "Row.inl"
#include "PARAM/PARAM.h"

namespace Param
{
	template<typename T>
	class Param
	{
		uint32_t m_numRows;
		std::vector<Row<T>> m_rows;

	public:
		static Param<T>* createFromFile(const wchar_t* filename)
		{
			size_t size;
			void* buffer;

			size_t bytesRead = RFile::allocAndLoad(filename, &buffer, &size);

			if (bytesRead > 0)
			{
				PARAM::PARAM<T>* paramFile = static_cast<PARAM::PARAM<T>*>(buffer);
				paramFile->locate();

				Param<T>* param = new Param<T>;
				param->m_numRows = paramFile->header.rowCount;
				param->m_rows.reserve(param->m_numRows);

				for (size_t i = 0; i < param->m_numRows; i++)
					param->m_rows.push_back(Row<T>(paramFile->rows[i].id, paramFile->rows[i].data, paramFile->rows[i].name));

				return param;
			}

			return nullptr;
		}

		Row<T>* getRowById(uint32_t id)
		{
			for (size_t i = 0; i < this->m_numRows; i++)
			{
				if (this->m_rows[i].getId() == id)
					return &this->m_rows[i];
			}

			return nullptr;
		}
	};
}