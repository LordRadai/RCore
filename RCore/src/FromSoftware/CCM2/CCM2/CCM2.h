#pragma once
#include "Header/Header.h"
#include "TexRegion/TexRegion.h"
#include "Glyph/Glyph.h"

namespace CCM2
{
	struct CCM2
	{
		UINT m_format;
		UINT m_fileSize;
		USHORT m_fontHeight;
		USHORT m_textureWidth;
		USHORT m_textureHeight;
		USHORT m_texRegionCount;
		USHORT m_glyphCount;
		USHORT m_sVar12;
		UINT m_iVar14;
		UINT m_glyphOffset;
		BYTE m_bVar1C;
		BYTE m_bVar1D;
		BYTE m_textureCount;
		BYTE m_bVar1F;
	};
}