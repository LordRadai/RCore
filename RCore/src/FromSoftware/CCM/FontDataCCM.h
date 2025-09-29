#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include "CCM/CCM.h"

namespace FontData
{
	class CodeGroup
	{
	};

	class Glyph
	{
	};

	class FontDataCCM
	{
		int m_format;
		int m_fontHeight;
		int m_textureWidth;
		int m_textureHeight;
		int m_numTextures;
		std::vector<CodeGroup*> m_codeGroups;
		std::vector<Glyph*> m_glyphs;

	public:
	};
}
