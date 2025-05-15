#pragma once
#include <fstream>
#include <Windows.h>

enum FileMode
{
	kFileModeNone = (1 << 0),
	kFileModeRead = (1 << 1),
	kFileModeWrite = (1 << 2)
};

class RFile
{
public:
	RFile() {}
	~RFile() {}

	static RFile* open(std::wstring fileName, int mode);
	static RFile* create(std::wstring fileName);
	void close();

	static size_t getFileSize(std::wstring fileName);
	static size_t allocAndLoad(std::wstring fileName, void** buffer, size_t* bufferSize, UINT alignment = 16);

	template <typename T> void read(T* pBuf)
	{
		this->m_file.read((char*)pBuf, sizeof(T));
	}

	template <typename T> void readArray(T* pBuf, size_t iCount)
	{
		this->m_file.read((char*)pBuf, iCount * sizeof(T));
	}

	template <typename T> void write(T v)
	{
		this->m_file.write((const char*)&v, sizeof(T));
	}

	template <typename T> void writeArray(T* pVal, size_t iCount)
	{
		this->m_file.write((const char*)pVal, iCount * sizeof(T));
	}

	void writePtr(int ptr)
	{
		this->m_file.write((char*)&ptr, 4);
	}

	void writeLongPtr(UINT64 ptr)
	{
		this->m_file.write((char*)&ptr, 8);
	}	
	
	void writeString(std::string string)
	{
		this->m_file.write(string.c_str(), string.length());
	}

	void writeString(std::wstring string)
	{
		this->writeArray(string.data(), string.size());
	}

	void pad(BYTE padVal, int count);
	void alignStream(UINT64 alignment);

	void seek(ptrdiff_t pos);
	ptrdiff_t tell();

private:
	std::fstream m_file;
	int m_mode = kFileModeNone;
};