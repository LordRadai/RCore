#include "CLIArgParser.h"
#include "RString/RString.h"

namespace RCLIArgParser
{
	std::wstring parseArgW(char* arg)
	{
		std::wstring result = L"";

		if (arg[0] == '-' && arg[1] == '-')
			result = RString::toWide(arg).substr(2);

		return result;
	}

	std::string parseArgA(char* arg)
	{
		std::string result = "";

		if (arg[0] == '-' && arg[1] == '-')
			result = std::string(arg).substr(2);

		return result;
	}
}