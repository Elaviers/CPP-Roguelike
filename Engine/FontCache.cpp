#include "FontCache.h"

#include "String.h"
#include <iostream>

FontCache::FontCache()
{
}


FontCache::~FontCache()
{
}

void FontCache::setLibrary(FT_Library& lib) {
	FT_LIB = &lib;
}

Font* FontCache::getFont(const char* path) {

	auto mit = _fontMap.find(path);

	if (mit == _fontMap.end()) {
		std::cout << "Caching font " << path << std::endl;
		Font font;
		font.init(*FT_LIB, path, 32);
		_fontMap.insert(std::make_pair(path, font));
		return getFont(path);
	}
	return &mit->second;
}
