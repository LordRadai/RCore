#include <filesystem>

#include "CCM2.h"
#include "RLog/RDebug/RDebug.h"
#include "RFile/RFile.h"
#include "RString/RString.h"

namespace CCM2
{
	Header::Header()
	{
		this->m_format = 0x20000; //CCM2
		this->m_fileSize = 0;
		this->m_fontHeight = 0;
		this->m_sVar12 = 0;
		this->m_iVar14 = 32;
		this->m_glyphOffset = 0;
		this->m_bVar1C = 4;
		this->m_bVar1D = 0;
		this->m_bVar1F = 0;

		this->calculateOffsets();
	}

	Header::Header(RFile* resource)
	{
		resource->read(&this->m_format);
		resource->read(&this->m_fileSize);
		resource->read(&this->m_fontHeight);
		resource->read(&this->m_textureWidth);
		resource->read(&this->m_textureHeight);
		resource->read(&this->m_texRegionCount);
		resource->read(&this->m_glyphCount);
		resource->read(&this->m_sVar12);
		resource->read(&this->m_iVar14);
		resource->read(&this->m_glyphOffset);
		resource->read(&this->m_bVar1C);
		resource->read(&this->m_bVar1D);
		resource->read(&this->m_textureCount);
		resource->read(&this->m_bVar1F);
	}

	Header::Header(int font_size, int texture_size, int texRegionCount, int glyphCount, int textureCount)
	{
		this->m_format = 0x20000;
		this->m_fileSize = 0;
		this->m_fontHeight = font_size;
		this->m_textureHeight = texture_size;
		this->m_textureWidth = texture_size;
		this->m_texRegionCount = texRegionCount;
		this->m_glyphCount = glyphCount;
		this->m_sVar12 = 0;
		this->m_iVar14 = 32;
		this->m_glyphOffset = 0;
		this->m_bVar1C = 4;
		this->m_bVar1D = 0;
		this->m_textureCount = textureCount;
		this->m_bVar1F = 0;

		this->calculateOffsets();
	}

	void Header::calculateOffsets()
	{
		this->m_fileSize = 32 + 8 * this->m_texRegionCount + 24 * this->m_glyphCount;
		this->m_glyphOffset = 32 + 8 * this->m_texRegionCount;
	}

	void Header::writeToFile(RFile* pOut)
	{
		pOut->write(this->m_format);
		pOut->write(this->m_fileSize);
		pOut->write(this->m_fontHeight);
		pOut->write(this->m_textureWidth);
		pOut->write(this->m_textureHeight);
		pOut->write(this->m_texRegionCount);
		pOut->write(this->m_glyphCount);
		pOut->write(this->m_sVar12);
		pOut->write(this->m_iVar14);
		pOut->write(this->m_glyphOffset);
		pOut->write(this->m_bVar1C);
		pOut->write(this->m_bVar1D);
		pOut->write(this->m_textureCount);
		pOut->write(this->m_bVar1F);
	}

	CCM2Reader::CCM2Reader()
	{
	}

	CCM2Reader::CCM2Reader(PWSTR pwPath)
	{
		this->m_init = true;
		this->m_filePath = pwPath;

		std::filesystem::path path(pwPath);

		RFile* resource = RFile::open(path, kFileModeRead);

		if (resource == nullptr)
		{
			this->m_init = false;
			return;
		}

		this->m_header = Header(resource);

		this->m_texRegions.reserve(this->m_header.m_texRegionCount);

		for (size_t i = 0; i < this->m_header.m_texRegionCount; i++)
			this->m_texRegions.push_back(TexRegion(pFile));

		for (size_t i = 0; i < this->m_header.m_glyphCount; i++)
			this->m_glyphs.push_back(Glyph(pFile));

		this->m_fileSize = this->m_header.m_fileSize;

		resource->close();
		delete resource;
	}

	CCM2Reader::~CCM2Reader()
	{
	}

	bool CCM2Reader::getInitStatus()
	{
		return this->m_init;
	}

	int CCM2Reader::getTexRegionCount()
	{
		return this->m_header.m_texRegionCount;
	}

	int CCM2Reader::getGlyphCount()
	{
		return this->m_header.m_glyphCount;
	}

	TexRegion* CCM2Reader::getTexRegion(int idx)
	{
		if (idx > this->m_header.m_texRegionCount)
			return nullptr;

		return &this->m_texRegions[idx];
	}

	Glyph* CCM2Reader::getGlyph(int idx)
	{
		if (idx > this->m_header.m_glyphCount)
			return nullptr;

		return &this->m_glyphs[idx];
	}

	void CCM2Reader::addTexRegion(TexRegion texRegion)
	{
		this->m_header.m_texRegionCount++;
		this->m_header.calculateOffsets();

		this->m_texRegions.push_back(texRegion);
	}

	void CCM2Reader::addGlyph(Glyph glyph)
	{
		this->m_header.m_glyphCount++;
		this->m_header.calculateOffsets();

		this->m_glyphs.push_back(glyph);
	}

	bool CCM2Reader::createCCM2(std::string pwPath, int font_size, int texture_size, int textureCount)
	{
		this->m_init = true;
		this->m_header.m_fontHeight = font_size;
		this->m_header.m_textureWidth = texture_size;
		this->m_header.m_textureHeight = texture_size;
		this->m_header.m_textureCount = textureCount;

		this->m_header.calculateOffsets();

		return this->writeFile(pwPath);
	}

	bool CCM2Reader::writeFile(std::string pwOutPath)
	{
		if (this->m_init == false)
			return false;

		std::filesystem::path path = pwOutPath;

		if (std::filesystem::exists(path))
		{
			std::filesystem::path bak_path = path;
			bak_path.replace_extension(L".ccm.bak");

			std::filesystem::copy_file(path, bak_path, std::filesystem::copy_options::overwrite_existing);
		}

		bool state = true;

		RFile* ccm_out = RFile::create(RString::toWide(pwOutPath));

		try
		{
			this->m_header.writeToFile(ccm_out);

			for (size_t i = 0; i < this->m_header.m_texRegionCount; i++)
				this->m_texRegions[i].WriteToFile(ccm_out);

			for (size_t i = 0; i < this->m_header.m_glyphCount; i++)
				this->m_glyphs[i].WriteToFile(ccm_out);
		}
		catch (const std::exception& e)
		{
			return;
		}

		ccm_out->close();
		delete ccm_out;

		return state;
	}
}