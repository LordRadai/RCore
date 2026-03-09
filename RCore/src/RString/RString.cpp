#include "RString.h"
#include <stringapiset.h>

std::string RString::replace(std::string str, std::string substr, std::string replacement)
{
	std::string new_str;
	size_t pos = str.find(substr);

	if (pos != std::string::npos) 
		str.replace(pos, substr.length(), replacement);

	new_str = str;

	return new_str;
}

std::string RString::guidToString(GUID guid)
{
	char guid_cstr[39];
	snprintf(guid_cstr, sizeof(guid_cstr),
		"%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
		guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);

	return std::string(guid_cstr);
}

std::wstring RString::shiftJisToWide(const char* str)
{
	int len = MultiByteToWideChar(932, 0, str, -1, NULL, 0);
	std::wstring wstr(len, L'\0');
	MultiByteToWideChar(932, 0, str, -1, &wstr[0], len);

	// Remove the null terminator
	if (!wstr.empty() && wstr.back() == L'\0')
		wstr.pop_back();

	return wstr;
}

std::string RString::shiftJisToUtf8(const char* str)
{
	std::string sjis(str);
	// Convert Shift-JIS -> UTF-16
	int wlen = MultiByteToWideChar(932, 0, sjis.c_str(), (int)sjis.size(), NULL, 0);
	std::wstring wstr(wlen, 0);
	MultiByteToWideChar(932, 0, sjis.c_str(), (int)sjis.size(), wstr.data(), wlen);

	// Convert UTF-16 -> UTF-8
	int u8len = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
	std::string utf8(u8len, 0);
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), wstr.size(), utf8.data(), u8len, NULL, NULL);

	return utf8;
}

std::string RString::wideToShiftJis(const std::wstring& wstr)
{
	// Convert UTF-16 -> Shift-JIS
	int sjislen = WideCharToMultiByte(932, 0, wstr.c_str(), (int)wstr.size(), NULL, 0, NULL, NULL);
	std::string sjis(sjislen, 0);
	WideCharToMultiByte(932, 0, wstr.c_str(), (int)wstr.size(), sjis.data(), sjislen, NULL, NULL);
	return sjis;
}

std::wstring RString::utf8ToWide(const std::string& str)
{
	std::string utf8(str);
	// Convert UTF-8 -> UTF-16
	int wlen = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), (int)utf8.size(), NULL, 0);
	std::wstring wstr(wlen, 0);
	MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), (int)utf8.size(), wstr.data(), wlen);
	return wstr;
}