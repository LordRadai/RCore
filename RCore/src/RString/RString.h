#pragma once
#include <Windows.h>
#include <ostream>
#include <string>
#include <sstream>
#include <iomanip>

namespace RString
{
	inline std::string toNarrow(const std::wstring& s)
	{
		return std::string(s.begin(), s.end());
	}

	inline std::string floatToString(float value, int precision = 3)
	{
		std::stringstream ss;
		ss << std::fixed << std::setprecision(precision) << value;
		return ss.str();
	}

	inline std::wstring toWide(const std::string& s)
	{
		return std::wstring(s.begin(), s.end());
	}

	std::string replace(std::string str, std::string substr, std::string replacement);
	std::string guidToString(GUID guid);
	std::wstring shiftJisToWide(const char* str);
}