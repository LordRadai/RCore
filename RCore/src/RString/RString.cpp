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