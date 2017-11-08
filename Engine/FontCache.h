#pragma once
#include "Font.h"
#include <map>

class String;

class FontCache
{
public:
	FontCache();
	~FontCache();

	void setLibrary(FT_Library& library);
	Font* getFont(const char* path);
private:
	std::map<String, Font> _fontMap;
	FT_Library* FT_LIB;
};
