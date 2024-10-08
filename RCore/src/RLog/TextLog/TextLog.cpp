#include <time.h>
#include <fstream>
#include <ostream>
#include <filesystem>
#include "TextLog.h"
#include "../RDebug/RDebug.h"

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

TextLog::TextLog()
{
    this->m_init = false;
    this->m_outPath = "";
}

TextLog::TextLog(std::string outPath)
{
    this->m_init = true;
    this->m_outPath = outPath;

    this->createLogFile();
}

TextLog::~TextLog()
{
    this->m_init = false;
    this->m_outPath = "";
}

bool TextLog::isInitialised()
{
    return this->m_init;
}

void TextLog::shutdown()
{
    this->m_ofstream.close();
}

void TextLog::setLogPath(std::string path)
{
    this->m_outPath = path;
}

std::string TextLog::getLogPath()
{
    return this->m_outPath;
}

bool TextLog::createLogFile()
{
    if (!this->m_init)
        return false;

    std::wstring parentPath = std::filesystem::path(this->m_outPath).parent_path();

    if (parentPath.compare(L""))
        std::filesystem::create_directories(parentPath);

    std::string filePath = this->m_outPath;

    this->m_ofstream = std::ofstream(filePath.c_str(), std::ios_base::out);

    return true;
}

bool TextLog::addLog(bool print_time, const char* fmt, ...)
{
    if (!this->m_init)
        return false;

    va_list args;
	__va_start(&args, fmt);
	std::string msg;

	char msg_buf[1000];

	msg = fmt;
	vsprintf_s(msg_buf, msg.c_str(), args);

    std::string filePath = this->m_outPath;
    std::string now = "[" + getCurrentDateTime("now") + "]";

    if (print_time)
        this->m_ofstream << now << '\t' << msg_buf;
    else
        this->m_ofstream << msg_buf;

    this->m_ofstream.flush();

    return true;
}