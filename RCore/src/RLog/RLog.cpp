#include <time.h>
#include <sstream>
#include "RLog.h"

inline std::string getCurrentDateTime(std::string format)
{
	time_t now = time(0);
	struct tm tstruct = *localtime(&now);
	char  buf[80];

	if (format.compare("now") == 0)
		strftime(buf, sizeof(buf), "%d-%m-%Y %X", &tstruct);
	else if (format.compare("date") == 0)
		strftime(buf, sizeof(buf), "%d-%m-%Y", &tstruct);
	else if (format.compare("time") == 0)
		strftime(buf, sizeof(buf), "%X", &tstruct);
	else
		RDebug::debuggerOut(MsgLevel_Error, MsgLevel_Error, "Invalid format type %s\n", format);

	return std::string(buf);
};

RLog::RLog()
{
	this->m_logLevel = MsgLevel_Debug;
	this->m_logFile = new TextLog();
	this->m_console = new RConsole();
	this->m_logPath = "";
}

RLog::RLog(MsgLevel level, std::string path, std::string log_name)
{
	this->m_logLevel = level;
	this->m_logFile = new TextLog(path);
	this->m_console = new RConsole(std::wstring(log_name.begin(), log_name.end()));
	this->m_logName = log_name;

	this->m_logPath = path;
}

RLog::~RLog()
{
}

void RLog::shutdown()
{
	this->m_logFile->shutdown();
}

void RLog::createLog(std::string path)
{
	this->m_logPath = path;

	this->m_logFile->setLogPath(path);
	this->m_logFile->createLogFile();
}

UINT RLog::getLogLevel()
{
	return this->m_logLevel;
}

void RLog::setLogLevel(UINT level)
{
	this->m_logLevel = level;
}

void RLog::debugMessage(MsgLevel level, const char* fmt, ...)
{
	if ((level - 1) > this->m_logLevel)
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
	vsprintf_s(msg, ("(threadId=" + thread_id + ")" + " " + msg_level + " " + msg_body).c_str(), args);

	std::string now = "[" + getCurrentDateTime("now") + "]";

	std::stringstream ss;
	ss << now << '\t' << msg;

	const char* msg_ptr = ss.str().c_str();

	RDebug::debuggerOut(this->m_logLevel, level, msg_ptr);

	if (this->m_logFile)
		this->m_logFile->addLog(msg_ptr);

	if (this->m_console)
		this->m_console->addLog(std::wstring(msg_ptr, msg_ptr + strlen(msg_ptr)).c_str());
}

void RLog::alertMessage(MsgLevel level, const char* fmt, ...)
{
	va_list args;
	__va_start(&args, fmt);

	char msg[BUFFER_SIZE];
	vsprintf_s(msg, fmt, args);

	std::string now = "[" + getCurrentDateTime("now") + "]";

	std::stringstream ss;
	ss << now << '\t' << msg;

	const char* msg_ptr = ss.str().c_str();

	RDebug::systemAlert(this->m_logLevel, level, this->m_logName.c_str(), msg_ptr);

	if (this->m_logFile)
		this->m_logFile->addLog(msg_ptr);

	if (this->m_console)
		this->m_console->addLog(std::wstring(msg_ptr, msg_ptr + strlen(msg_ptr)).c_str());
}

void RLog::panicMessage(const char* fmt, ...)
{
	va_list args;
	__va_start(&args, fmt);

	char msg[BUFFER_SIZE];
	vsprintf_s(msg, fmt, args);

	std::string now = "[" + getCurrentDateTime("now") + "]";

	std::stringstream ss;
	ss << now << '\t' << msg;

	const char* msg_ptr = ss.str().c_str();

	if (this->m_logFile)
		this->m_logFile->addLog(msg_ptr);

	if (this->m_console)
		this->m_console->addLog(std::wstring(msg_ptr, msg_ptr + strlen(msg_ptr)).c_str());

	RDebug::systemPanic(this->m_logName.c_str(), msg_ptr);
}

void RLog::addEntry(bool print_time, const char* fmt, ...)
{
	va_list args;
	__va_start(&args, fmt);

	char msg[BUFFER_SIZE];
	vsprintf_s(msg, fmt, args);

	if (this->m_logFile)
		this->m_logFile->addLog(fmt, args);

	if (this->m_console)
		this->m_console->addLog(std::wstring(msg, msg + strlen(msg)).c_str());
}