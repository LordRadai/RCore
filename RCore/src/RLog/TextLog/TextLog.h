#pragma once
#include <fstream>

class TextLog
{
public:
	TextLog();
	TextLog(std::string outPath);
	~TextLog();

	bool isInitialised();
	void shutdown();

	void setLogPath(std::string path);
	std::string getLogPath();

	bool createLogFile();
	bool addLog(const char* fmt, ...);

private:
	bool m_init;
	std::string m_outPath;
	std::ofstream m_ofstream;
};