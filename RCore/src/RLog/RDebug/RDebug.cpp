#include "RDebug.h"

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

void RDebug::systemPanic(const char* src_module, const char* fmt, ...)
{
	va_list args;
	__va_start(&args, fmt);

	char msg[BUFFER_SIZE];

	vsprintf_s(msg, fmt, args);

	std::string txt_log_msg = "FATAL ERROR:" + std::string(msg);
	txt_log_msg.erase(std::remove(txt_log_msg.begin(), txt_log_msg.end(), '\n'));

	try
	{
		throw std::exception(msg);
	}
	catch (std::exception& e)
	{
		ShowCursor(true);
		MessageBoxA(NULL, e.what(), src_module, MB_ICONERROR);
	}

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
		systemPanic(src_module, "Invalid debug level\n");
		return;
	}

	ShowCursor(true);
	MessageBoxA(NULL, msg, src_module, icon);
}