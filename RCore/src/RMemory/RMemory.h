#pragma once
#include <Windows.h>
#include <cstdint>
#include <cstring>
#include <type_traits>

namespace RMemory
{
	//Aligns value to a power of 2 alignment
	size_t align(size_t value, size_t alignment);

	inline uint32_t extractBits(int value, int shiftValue, int mask)
	{
		return (uint32_t)(value >> shiftValue) & mask;
	}

	template <typename T> inline void fixPtr(T*& ptr, void* base)
	{
		if (ptr != nullptr)
			ptr = reinterpret_cast<T*>((char*)ptr + (ptrdiff_t)base);
	}

	inline ptrdiff_t getOffset(void* ptr, void* base)
	{
		if (ptr != nullptr)
			return (char*)ptr - (char*)base;
	}

	template <typename T>
	T endianSwap(T value) 
	{
		static_assert(std::is_fundamental<T>::value, "endian_swap requires a fundamental type");

		T result;
		uint8_t* src = reinterpret_cast<uint8_t*>(&value);
		uint8_t* dst = reinterpret_cast<uint8_t*>(&result);

		size_t n = sizeof(T);
		for (size_t i = 0; i < n; ++i)
			dst[i] = src[n - 1 - i];

		return result;
	}
}