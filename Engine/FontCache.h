#pragma once
#include "Font.h"

#include <map>

class FontCache
{
public:
	FontCache();
	~FontCache();

	void setLibrary(FT_Library& library);
	Font* getFont(const std::string& path);
private:
	std::map<std::string,Font> _fontMap;
	FT_Library* FT_LIB;
};
