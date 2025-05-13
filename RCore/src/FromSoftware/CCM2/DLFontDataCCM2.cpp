#include <filesystem>

#include "DLFontDataCCM2.h"
#include "RLog/RDebug/RDebug.h"
#include "RFile/RFile.h"
#include "RString/RString.h"

Glyph* DLFontDataCCM2::getGlyph(int idx)
{
	if (idx > this->m_glyphs.size())
		return nullptr;

	return this->m_glyphs[idx];
}

void DLFontDataCCM2::addGlyph(Glyph glyph)
{
}

DLFontDataCCM2* DLFontDataCCM2::create(int font_size, int texture_size, int textureCount)
{
	DLFontDataCCM2* ccm2 = new DLFontDataCCM2();

	ccm2->m_init = true;
	ccm2->m_fontHeight = font_size;
	ccm2->m_textureWidth = texture_size;
	ccm2->m_textureHeight = texture_size;
	ccm2->m_numTextures = textureCount;

	return ccm2;
}

DLFontDataCCM2* DLFontDataCCM2::loadFile(std::wstring path)
{
	UINT64 size;
	void* buffer;

	UINT64 bytesRead = RFile::allocAndLoad(path, &buffer, &size);

	if (bytesRead > 0)
	{
		CCM2::CCM2* ccm2 = static_cast<CCM2::CCM2*>(buffer);

		DLFontDataCCM2* fontData = new DLFontDataCCM2();
		size_t fileSize = ccm2->getMemoryRequirements();

		return timeAct;
	}
}

bool DLFontDataCCM2::save(std::string pwOutPath)
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

	RFile* ccm_out = RFile::create(RString::toWide(pwOutPath));

	ccm_out->close();
	delete ccm_out;

	return true;
}