#pragma once
#include <cstdint>
#include <string>

namespace Param
{
	template<typename T>
	class Row
	{
		uint32_t id;
		T* data;
		std::string name;
	public:
		Row(uint32_t id, T* data, const char* name)
		{
			this->id = id;
			this->data = new T;
			memcpy(this->data, data, sizeof(T));

			this->name = std::string(name);
		}

		~Row()
		{
			if (this->data)
			{
				delete this->data;
				this->data = nullptr;
			}
		}

		uint32_t getId() const { return this->id; }
		T* getData() const { return this->data; }
		std::string getName() const { return this->name; }
	};
}
