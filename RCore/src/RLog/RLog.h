#pragma once
#include "RConsole/RConsole.h"
#include "RDebug/RDebug.h"
#include "TextLog/TextLog.h"

class RLog
{
public:
	RLog();
	RLog(MsgLevel level, std::string path, std::string log_name);
	~RLog();

	void shutdown();

	void createLog(std::string path);
	UINT getLogLevel();
	void setLogLevel(UINT level);

	void debugMessage(MsgLevel level, const char* fmt, ...);
	void alertMessage(MsgLevel level, const char* fmt, ...);

	void addEntry(bool print_time, const char* fmt, ...);
	void setConsoleVisibility(bool bVisible) { this->m_console->setVisibility(bVisible); };
private:
	UINT m_logLevel;
	TextLog* m_logFile;
	RConsole* m_console;
	std::string m_logPath;
	std::string m_logName;
};