#include <filesystem>
#include <assert.h>
#include "FontDataCCM.h"
#include "RMemory/RMemory.h"

namespace FontDataCCM
{
	CodeGroup* CodeGroup::create(int startCode, int endCode, int glyphIndex)
	{
		CodeGroup* codeGroup = new CodeGroup();
		codeGroup->m_startCode = startCode;
		codeGroup->m_endCode = endCode;
		codeGroup->m_glyphIndex = glyphIndex;

		return codeGroup;
	}

	CodeGroup* CodeGroup::createFromResource(CCM::CodeGroup* resource, char* ptr, bool bBigEndian)
	{
		CodeGroup* codeGroup = new CodeGroup();

		if (bBigEndian)
			*resource = resource->endianSwap();
		
		codeGroup->m_startCode = resource->startCode;
		codeGroup->m_endCode = resource->endCode;
		codeGroup->m_glyphIndex = resource->glyphIndex;
		return codeGroup;
	}

	void CodeGroup::destroy()
	{
		delete this;
	}

	int CodeGroup::getMemoryRequirements()
	{
		return sizeof(CCM::CodeGroup);
	}

	CCM::CodeGroup CodeGroup::generateBinary(RFile* file, bool bBigEndian)
	{
		CCM::CodeGroup codeGroup;
		codeGroup.startCode = this->m_startCode;
		codeGroup.endCode = this->m_endCode;
		codeGroup.glyphIndex = this->m_glyphIndex;

		if (bBigEndian)
			codeGroup = codeGroup.endianSwap();

		file->write(codeGroup);
		return codeGroup;
	}

	Glyph* Glyph::create(float u1, float v1, float u2, float v2, short textureIdx, short preSpace, short width, short advance)
	{
		Glyph* glyph = new Glyph();
		glyph->m_u1 = u1;
		glyph->m_v1 = v1;
		glyph->m_u2 = u2;
		glyph->m_v2 = v2;
		glyph->m_textureIndex = textureIdx;
		glyph->m_preSpace = preSpace;
		glyph->m_width = width;
		glyph->m_advance = advance;

		return glyph;
	}

	Glyph* Glyph::createFromResource(CCM::Glyph* resource, char* ptr, bool bBigEndian)
	{		
		Glyph* glyph = new Glyph();

		if (bBigEndian)
			*resource = resource->endianSwap();
		
		glyph->m_u1 = resource->u1;
		glyph->m_v1 = resource->v1;
		glyph->m_u2 = resource->u2;
		glyph->m_v2 = resource->v2;
		glyph->m_textureIndex = resource->textureIndex;
		glyph->m_preSpace = resource->prespace;
		glyph->m_width = resource->width;
		glyph->m_advance = resource->advance;

		return glyph;
	}

	void Glyph::destroy()
	{
		delete this;
	}

	int Glyph::getMemoryRequirements()
	{
		return sizeof(CCM::Glyph);
	}

	CCM::Glyph Glyph::generateBinary(RFile* file, bool bBigEndian)
	{
		CCM::Glyph glyph;
		glyph.u1 = this->m_u1;
		glyph.v1 = this->m_v1;
		glyph.u2 = this->m_u2;
		glyph.v2 = this->m_v2;
		glyph.prespace = this->m_preSpace;
		glyph.width = this->m_width;
		glyph.advance = this->m_advance;
		glyph.textureIndex = this->m_textureIndex;

		if (bBigEndian)
			glyph = glyph.endianSwap();

		file->write(glyph);

		return glyph;
	}

	FontDataCCM* FontDataCCM::create(int font_size, int texture_size)
	{
		FontDataCCM* fontData = new FontDataCCM();
		fontData->m_format = 1;
		fontData->m_fontHeight = font_size;
		fontData->m_textureWidth = texture_size;
		fontData->m_textureHeight = texture_size;
		fontData->m_numTextures = 1;
		fontData->m_init = true;

		return fontData;
	}

	FontDataCCM* FontDataCCM::loadFile(std::wstring path)
	{
		int64_t size;
		void* buffer;
		int64_t bytesRead = RFile::allocAndLoad(path, &buffer, &size, 4);

		if (bytesRead > 0)
		{
			CCM::CCM* ccm = static_cast<CCM::CCM*>(buffer);
			const bool bBigEndian = ccm->isBigEndian;

			if (bBigEndian)
				*ccm = ccm->endianSwap();
		
			FontDataCCM* fontData = new FontDataCCM();
			fontData->m_fileName = std::filesystem::path(path).filename();
			fontData->m_filePath = path;
			fontData->m_fileSize = bytesRead;
			fontData->m_bBigEndian = bBigEndian;
			fontData->m_numTextures = ccm->textureCount;
			fontData->m_fontHeight = ccm->fontHeight;
			fontData->m_textureWidth = ccm->textureWidth;
			fontData->m_textureHeight = ccm->textureHeight;
			CCM::Glyph* pGlyphs = (CCM::Glyph*)ccm->glyphOffset;

			RMemory::fixPtr(pGlyphs, ccm);
			for (size_t i = 0; i < ccm->glyphCount; i++)
				fontData->m_glyphs.push_back(Glyph::createFromResource(&pGlyphs[i], (char*)ccm, bBigEndian));

			fontData->m_init = true;

			return fontData;
		}

		return nullptr;
	}

	void FontDataCCM::destroy()
	{
		for (size_t i = 0; i < this->m_codeGroups.size(); i++)
			this->m_codeGroups[i]->destroy();

		for (size_t i = 0; i < this->m_glyphs.size(); i++)
			this->m_glyphs[i]->destroy();

		delete this;
	}

	int FontDataCCM::getMemoryRequirements()
	{
		int size = sizeof(CCM::CCM);

		for (size_t i = 0; i < this->m_codeGroups.size(); i++)
			size += this->m_codeGroups[i]->getMemoryRequirements();

		for (size_t i = 0; i < this->m_glyphs.size(); i++)
			size += this->m_glyphs[i]->getMemoryRequirements();

		return size;
	}

	void FontDataCCM::addGlyph(Glyph* glyph)
	{
		if (glyph == nullptr)
			return;

		this->m_glyphs.push_back(glyph);
	}

	bool FontDataCCM::save(std::wstring path, bool bBigEndian)
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

		RFile* file = RFile::create(filepath);

		if (file == nullptr || file->isOpen() == false)
			return false;

		this->m_bBigEndian = bBigEndian;
		this->generateBinary(file, bBigEndian);
		file->close();

		delete file;
		return true;
	}

	CCM::CCM FontDataCCM::generateBinary(RFile* file, bool bBigEndian)
	{
		CCM::CCM ccm;
		ccm.format = 0x10000;
		ccm.fileSize = this->getMemoryRequirements();
		ccm.fontHeight = this->m_fontHeight;
		ccm.textureWidth = this->m_textureWidth;
		ccm.textureHeight = this->m_textureHeight;
		ccm.sVarE = sizeof(CCM::CCM);
		ccm.codeGroupCount = 0;
		ccm.glyphCount = (USHORT)this->m_glyphs.size();
		ccm.codeGroupOffset = sizeof(CCM::CCM);
		ccm.glyphOffset = sizeof(CCM::CCM) + ccm.codeGroupCount * sizeof(CCM::CodeGroup);
		ccm.bVar1C = 1;
		ccm.isBigEndian = this->m_bBigEndian;
		ccm.textureCount = (BYTE)this->m_numTextures;

		if (bBigEndian)
			ccm = ccm.endianSwap();

		file->write(ccm);

		FILE_ASSERT_POS(file, ccm.codeGroupOffset);

		for (size_t i = 0; i < this->m_codeGroups.size(); i++)
			this->m_codeGroups[i]->generateBinary(file, bBigEndian);

		FILE_ASSERT_POS(file, ccm.glyphOffset);
		
		for (size_t i = 0; i < this->m_glyphs.size(); i++)
			this->m_glyphs[i]->generateBinary(file, bBigEndian);

		FILE_ASSERT_POS(file, ccm.fileSize);

		return ccm;
	}
}
