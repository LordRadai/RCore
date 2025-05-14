#pragma once
#include <Windows.h>
#include <string>

namespace RCLIArgParser
{
	std::wstring parseArgW(char* arg);
	std::string parseArgA(char* arg);
}