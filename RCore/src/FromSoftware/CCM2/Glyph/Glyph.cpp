#include "Glyph.h"

namespace CCM2
{
	Glyph::Glyph(RFile* resource)
	{
		resource->read(&this->m_code);
		resource->read(&this->m_texRegionOffset);
		resource->read(&this->m_textureIndex);
		resource->read(&this->m_preSpace);
		resource->read(&this->m_width);
		resource->read(&this->m_advance);
		resource->read(&this->m_iVar10);
		resource->read(&this->m_iVar14);
	}

	Glyph::Glyph(WCHAR code, int idx, short textureIdx, short preSpace, short width, short advance)
	{
		this->m_code = code;
		this->m_texRegionOffset = 0x20 + 8 * idx;
		this->m_textureIndex = textureIdx;
		this->m_preSpace = preSpace;
		this->m_width = width;
		this->m_advance = advance;
		this->m_iVar10 = 0;
		this->m_iVar14 = 0;
	}

	bool Glyph::writeToFile(RFile* pOut)
	{
		pOut->write(this->m_code);
		pOut->write(this->m_texRegionOffset);
		pOut->write(this->m_textureIndex);
		pOut->write(this->m_preSpace);
		pOut->write(this->m_width);
		pOut->write(this->m_advance);
		pOut->write(this->m_iVar10);
		pOut->write(this->m_iVar14);

		return true;
	}
}