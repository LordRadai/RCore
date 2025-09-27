#include <fstream>
#include <ostream>
#include "RFileSystem/RFileSystem.h"
#include "TextLog.h"
#include "../RDebug/RDebug.h"

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

    std::wstring parentPath = std_fs::path(this->m_outPath).parent_path().wstring();

    if (parentPath.compare(L""))
        std_fs::create_directories(parentPath);

    std::string filePath = this->m_outPath;

    this->m_ofstream = std::ofstream(filePath.c_str(), std::ios_base::out);

    return true;
}

bool TextLog::addLog(const char* fmt, ...)
{
    if (!this->m_init)
        return false;

    va_list args;
	__va_start(&args, fmt);
	std::string msg;

	char msg_buf[1000];

	msg = fmt;
	vsprintf_s(msg_buf, msg.c_str(), args);

	va_end(args);

	this->m_ofstream << msg_buf;
    this->m_ofstream.flush();

    return true;
}