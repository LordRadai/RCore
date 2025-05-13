#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include "CCM2/CCM2.h"

class TexRegion
{
public:
	static TexRegion* create(short x1, short y1, short x2, short y2);
	static TexRegion* createFromResource(CCM2::TexRegion* resource);

private:
	TexRegion() {}
	~TexRegion() {}

	int getMemoryRequirements();
	CCM2::TexRegion generateBinary(RFile* file);

	short m_x1 = 0;
	short m_y1 = 0;
	short m_x2 = 0;
	short m_y2 = 0;
};

class Glyph
{
public:
	static Glyph* create(int code, int idx, short textureIdx, short preSpace, short width, short advance);
	static Glyph* createFromResource(CCM2::Glyph* resource);

	int getCode() const { return this->m_code; }
	int getTexRegionOffset() const { return this->m_texRegionOffset; }
	short getTextureIndex() const { return this->m_textureIndex; }
	short getPreSpace() const { return this->m_preSpace; }
	short getWidth() const { return this->m_width; }
	short getAdvance() const { return this->m_advance; }

private:
	Glyph() {}
	~Glyph() {}

	int getMemoryRequirements();
	CCM2::Glyph generateBinary(RFile* file);

	int m_code = 0;
	int m_texRegionOffset = 0;
	short m_textureIndex = 0;
	short m_preSpace = 0;
	short m_width = 0;
	short m_advance = 0;

	TexRegion* m_texRegion = nullptr;
};

class DLFontDataCCM2
{
public:
	static DLFontDataCCM2* create(int font_size, int texture_size, int textureCount);
	static DLFontDataCCM2* loadFile(std::wstring path);

	bool getInitStatus() const { return this->m_init; }

	int getGlyphCount() const { return this->m_glyphs.size(); }
	Glyph* getGlyph(int idx);

	void addGlyph(Glyph glyph);

	bool save(std::string path);

protected:
	DLFontDataCCM2() {}
	~DLFontDataCCM2() {}

	int getMemoryRequirements();
	CCM2::CCM2 generateBinary(RFile* file);

	std::wstring m_fileName;
	std::wstring m_filePath;
	size_t m_fileSize;
	bool m_init = false;

	int m_fontHeight = 0;
	int m_textureWidth = 0;
	int m_textureHeight = 0;
	int m_numTextures = 0;

	std::vector<TexRegion*> m_texRegions;
	std::vector<Glyph*> m_glyphs;
};