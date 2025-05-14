#include <filesystem>
#include <assert.h>

#include "DLFontDataCCM2.h"
#include "RLog/RDebug/RDebug.h"
#include "RFile/RFile.h"
#include "RString/RString.h"
#include "RMemory/RMemory.h"

TexRegion* TexRegion::create(short x1, short y1, short x2, short y2)
{
	TexRegion* texRegion = new TexRegion();
	texRegion->m_x1 = x1;
	texRegion->m_y1 = y1;
	texRegion->m_x2 = x2;
	texRegion->m_y2 = y2;
	return texRegion;
}

TexRegion* TexRegion::createFromResource(CCM2::TexRegion* resource)
{
	TexRegion* texRegion = new TexRegion();

	texRegion->m_x1 = resource->x1;
	texRegion->m_y1 = resource->y1;
	texRegion->m_x2 = resource->x2;
	texRegion->m_y2 = resource->y2;

	return texRegion;
}

void TexRegion::destroy()
{
	delete this;
}

int TexRegion::getMemoryRequirements()
{
	return sizeof(CCM2::TexRegion);
}

CCM2::TexRegion TexRegion::generateBinary(RFile* file)
{
	CCM2::TexRegion texRegion;

	texRegion.x1 = this->m_x1;
	texRegion.y1 = this->m_y1;
	texRegion.x2 = this->m_x2;
	texRegion.y2 = this->m_y2;

	file->write(texRegion);

	return texRegion;
}

Glyph* Glyph::create(int code, int idx, short textureIdx, short preSpace, short width, short advance, TexRegion* pTexRegion)
{
	Glyph* glyph = new Glyph();

	glyph->m_code = code;
	glyph->m_texRegion = pTexRegion;
	glyph->m_textureIndex = textureIdx;
	glyph->m_preSpace = preSpace;
	glyph->m_width = width;
	glyph->m_advance = advance;

	return glyph;
}

int Glyph::getMemoryRequirements()
{
	return sizeof(CCM2::Glyph) + this->m_texRegion->getMemoryRequirements();
}

Glyph* Glyph::createFromResource(CCM2::Glyph* resource, char* ptr)
{
	Glyph* glyph = new Glyph();

	glyph->m_code = resource->code;
	glyph->m_textureIndex = resource->textureIndex;
	glyph->m_preSpace = resource->preSpace;
	glyph->m_width = resource->width;
	glyph->m_advance = resource->advance;

	CCM2::TexRegion* texRegion = (CCM2::TexRegion*)resource->texRegionOffset;
	RMemory::fixPtr(texRegion, ptr);

	glyph->m_texRegion = TexRegion::createFromResource(texRegion);

	return glyph;
}

void Glyph::destroy()
{
	if (this->m_texRegion)
		this->m_texRegion->destroy();

	delete this;
}

CCM2::Glyph Glyph::generateBinary(RFile* file, int glyphIdx)
{
	CCM2::Glyph glyph;

	glyph.code = this->m_code;
	glyph.texRegionOffset = glyphIdx * sizeof(CCM2::TexRegion) + sizeof(CCM2::CCM2);
	glyph.textureIndex = this->m_textureIndex;
	glyph.preSpace = this->m_preSpace;
	glyph.width = this->m_width;
	glyph.advance = this->m_advance;
	glyph.iVar10 = 0;
	glyph.iVar14 = 0;

	file->write(glyph);

	return glyph;
}

void DLFontDataCCM2::destroy()
{
	for (size_t i = 0; i < this->m_glyphs.size(); i++)
		this->m_glyphs[i]->destroy();
}

Glyph* DLFontDataCCM2::getGlyph(int idx)
{
	if (idx > this->m_glyphs.size())
		return nullptr;

	return this->m_glyphs[idx];
}

void DLFontDataCCM2::addGlyph(Glyph* glyph)
{
	if (this->m_init == false)
		return;

	if (glyph == nullptr)
		return;

	this->m_glyphs.push_back(glyph);
}

DLFontDataCCM2* DLFontDataCCM2::create(int font_size, int texture_size)
{
	DLFontDataCCM2* ccm2 = new DLFontDataCCM2();

	ccm2->m_init = true;
	ccm2->m_fontHeight = font_size;
	ccm2->m_textureWidth = texture_size;
	ccm2->m_textureHeight = texture_size;
	ccm2->m_numTextures = 0;

	return ccm2;
}

DLFontDataCCM2* DLFontDataCCM2::loadFile(std::wstring path)
{
	UINT64 size;
	void* buffer;

	UINT64 bytesRead = RFile::allocAndLoad(path, &buffer, &size, 4);

	if (bytesRead > 0)
	{
		CCM2::CCM2* ccm2 = static_cast<CCM2::CCM2*>(buffer);

		DLFontDataCCM2* fontData = new DLFontDataCCM2();

		fontData->m_fileName = std::filesystem::path(path).filename();
		fontData->m_filePath = path;
		fontData->m_fileSize = bytesRead;

		fontData->m_numTextures = ccm2->textureCount;
		fontData->m_fontHeight = ccm2->fontHeight;
		fontData->m_textureWidth = ccm2->textureWidth;
		fontData->m_textureHeight = ccm2->textureHeight;

		CCM2::Glyph* pGlyphs = (CCM2::Glyph*)ccm2->glyphOffset;
		RMemory::fixPtr(pGlyphs, ccm2);

		for (size_t i = 0; i < ccm2->glyphCount; i++)
			fontData->m_glyphs.push_back(Glyph::createFromResource(&pGlyphs[i], (char*)ccm2));

		fontData->m_init = true;

		return fontData;
	}
}

int DLFontDataCCM2::getMemoryRequirements()
{
	int size = sizeof(CCM2::CCM2);

	for (size_t i = 0; i < this->m_glyphs.size(); i++)
		size += this->m_glyphs[i]->getMemoryRequirements();

	return size;
}

CCM2::CCM2 DLFontDataCCM2::generateBinary(RFile* file)
{
	CCM2::CCM2 ccm2;
	ccm2.format = 0x20000;
	ccm2.fileSize = this->getMemoryRequirements();
	ccm2.fontHeight = this->m_fontHeight;
	ccm2.textureWidth = this->m_textureWidth;
	ccm2.textureHeight = this->m_textureHeight;
	ccm2.texRegionCount = (USHORT)this->m_glyphs.size();
	ccm2.glyphCount = (USHORT)this->m_glyphs.size();
	ccm2.pad[0] = 0;
	ccm2.pad[1] = 0;
	ccm2.texRegionOffset = sizeof(CCM2::CCM2);
	ccm2.glyphOffset = ccm2.texRegionCount * sizeof(CCM2::TexRegion) + sizeof(CCM2::CCM2);
	ccm2.alignment = 4;
	ccm2.textureCount = (USHORT)this->m_numTextures;

	file->write(ccm2);
	ptrdiff_t pos = file->tell();
	assert(pos == ccm2.texRegionOffset);

	for (size_t i = 0; i < this->m_glyphs.size(); i++)
		this->m_glyphs[i]->m_texRegion->generateBinary(file);

	pos = file->tell();
	assert(pos == ccm2.glyphOffset);

	for (size_t i = 0; i < this->m_glyphs.size(); i++)
		this->m_glyphs[i]->generateBinary(file, i);

	pos = file->tell();
	assert(pos == ccm2.fileSize);

	return ccm2;
}

bool DLFontDataCCM2::save(std::wstring path)
{
	if (this->m_init == false)
		return false;

	std::filesystem::path filepath = path;
	std::filesystem::create_directories(filepath.parent_path());

	if (std::filesystem::exists(filepath))
	{
		std::filesystem::path bak_path = filepath;
		bak_path.replace_extension(L".ccm.bak");

		std::filesystem::copy_file(filepath, bak_path, std::filesystem::copy_options::overwrite_existing);
	}

	RFile* fileRes = RFile::create(path);

	CCM2::CCM2 ccm2 = this->generateBinary(fileRes);

	return true;
}