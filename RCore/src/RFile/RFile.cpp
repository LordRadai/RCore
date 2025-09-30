#include "RFile.h"
#include "RMemory/RMemory.h"

RFile* RFile::open(std::wstring fileName, int mode)
{
	RFile* file = new RFile;

	std::ios::openmode openMode = std::ios::binary;

	if (mode & kFileModeRead)
		openMode |= std::ios::in;

	if (mode & kFileModeWrite)
		openMode |= std::ios::out;

	file->m_file.open(fileName, openMode);
	file->m_mode = mode;

	return file;
}

RFile* RFile::create(std::wstring fileName)
{
	RFile* file = new RFile;

	file->m_file.open(fileName, std::ios::binary | std::ios::out);
	file->m_mode = kFileModeWrite;

	return file;
}

void RFile::close()
{
	this->m_file.close();
}

size_t RFile::getFileSize(std::wstring fileName)
{
	std::ifstream file;
	file.open(fileName, std::ios::binary | std::ios::ate);
	
	UINT64 size = file.tellg();
	file.close();

	return size;
}

int64_t RFile::allocAndLoad(std::wstring fileName, void** buffer, int64_t* bufferSize, UINT alignment)
{
	std::ifstream file;

	file.open(fileName, std::ios::binary | std::ios::in);

	if (!file.is_open())
	{
		*bufferSize = -1;
		return -1;
	}

	int64_t size = getFileSize(fileName);

	*bufferSize = RMemory::align(size, alignment);

	*buffer = new char[*bufferSize];

	file.read((char*)(*buffer), size);
	file.close();

	return *bufferSize;
}

void RFile::pad(BYTE padVal, int count)
{
	BYTE* pPaddingVal = new BYTE[count];

	for (size_t i = 0; i < count; i++)
		pPaddingVal[i] = padVal;

	writeArray(pPaddingVal, count);

	delete[] pPaddingVal;
}

void RFile::alignStream(UINT64 alignment)
{
	UINT64 alignedValue = RMemory::align(this->tell(), alignment);

	this->seek(alignedValue);
}

void RFile::seek(ptrdiff_t pos)
{
	this->m_file.seekp(pos);
	this->m_file.seekg(pos);
}

ptrdiff_t RFile::tell()
{
	ptrdiff_t tellg = this->m_file.tellg();
	ptrdiff_t tellp = this->m_file.tellp();

	if (tellg == 0)
		return tellp;

	return tellg;
}