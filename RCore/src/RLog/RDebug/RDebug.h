#pragma once
#include <windows.h>
#include <string>
#include <debugapi.h>

#define BUFFER_SIZE 1024

enum MsgLevel
{
	MsgLevel_Info = 1000000001,
	MsgLevel_Warn = 1300000001,
	MsgLevel_Error = 1400000001,
	MsgLevel_Debug = 2000000001,
};

enum PanicMode
{
	PanicMode_Throw,
	PanicMode_InvokeDebugger,
	PanicMode_Abort
};

namespace RDebug
{
	void debuggerOut(UINT usr_level, MsgLevel level, const char* fmt, ...);
	void systemPanic(const char* src_module, int lineNum, const char* msg, ...);
	void systemAlert(UINT usr_level, MsgLevel level, const char* src_module, const char* fmt, ...);

	void setPanicMode(PanicMode mode);
}

#define INVOKE_PANIC(fmt, ...) RDebug::systemPanic(__FILE__, __LINE__, fmt, ##__VA_ARGS__)