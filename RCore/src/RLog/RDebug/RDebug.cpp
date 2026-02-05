#include <stdexcept>
#include "RDebug.h"

PanicMode s_panicMode = PanicMode_Abort;

void RDebug::debuggerOut(UINT usr_level, MsgLevel level, const char* fmt, ...)
{
	if ((level - 1) > usr_level)
		return;

	va_list args;
	__va_start(&args, fmt);
	std::string msg_level;
	std::string msg_body;
	std::string thread_id = std::to_string(GetCurrentThreadId());

	char msg[BUFFER_SIZE];

	switch (level)
	{
	case MsgLevel_Debug:
		msg_level = "[DEBUG]";
		break;
	case MsgLevel_Info:
		msg_level = "[INFO]";
		break;
	case MsgLevel_Warn:
		msg_level = "[WARN]";
		break;
	case MsgLevel_Error:
		msg_level = "[ERROR]";
		break;
	default:
		break;
	}

	msg_body = fmt;
	vsprintf_s(msg, ("(threadId=" + thread_id + ")" +  " " + msg_level + " " + msg_body).c_str(), args);

#ifdef _CONSOLE
	printf_s(msg);
#endif

	std::string txt_log_msg = std::string(msg);

	OutputDebugStringA(msg);
}

void RDebug::systemPanic(const char* src_module, int lineNum, const char* fmt, ...)
{
	va_list args;
	__va_start(&args, fmt);

	char msg[BUFFER_SIZE];

	vsprintf_s(msg, fmt, args);

	char header[BUFFER_SIZE];
	sprintf_s(header, "System panic! (%s, %d): \n", src_module, lineNum);

	std::string txt_log_msg = header + std::string(msg);
	txt_log_msg.erase(std::remove(txt_log_msg.begin(), txt_log_msg.end(), '\n'));

	switch (s_panicMode)
	{
	case PanicMode_Throw:
		throw std::runtime_error(txt_log_msg);
		break;
	case PanicMode_Abort:
		break;
	case PanicMode_InvokeDebugger:
		OutputDebugStringA(txt_log_msg.c_str());
		__debugbreak();
		break;
	default:
		break;
	}

	OutputDebugStringA(txt_log_msg.c_str());
	abort();
}

void RDebug::systemAlert(UINT usr_level, MsgLevel level, const char* src_module, const char* fmt, ...)
{
	if ((level - 1) > usr_level)
		return;

	va_list args;
	__va_start(&args, fmt);

	char msg[BUFFER_SIZE];
	UINT icon = MB_ICONASTERISK;

	vsprintf_s(msg, fmt, args);

	RDebug::debuggerOut(usr_level, level, fmt, args);

	switch (level)
	{
	case MsgLevel_Debug:
		icon = MB_ICONINFORMATION;
		break;
	case MsgLevel_Info:
		icon = MB_ICONINFORMATION;
		break;
	case MsgLevel_Warn:
		icon = MB_ICONEXCLAMATION;
		break;
	case MsgLevel_Error:
		icon = MB_ICONERROR;
		break;
	default:
		INVOKE_PANIC("Invalid message level %d.", level);
		return;
	}

	ShowCursor(true);
	MessageBoxA(NULL, msg, src_module, icon);
}

void RDebug::setPanicMode(PanicMode mode)
{
	s_panicMode = mode;
}