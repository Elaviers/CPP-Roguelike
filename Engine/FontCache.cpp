#include "FontCache.h"

#include <iostream>
#include <string>

FontCache::FontCache()
{
}


FontCache::~FontCache()
{
}

void FontCache::setLibrary(FT_Library& lib) {
	FT_LIB = &lib;
}

Font* FontCache::getFont(const std::string& path) {

	auto mit = _fontMap.find(path);

	if (mit == _fontMap.end()) {
		std::cout << "Caching font " << path << std::endl;
		Font font;
		font.init(*FT_LIB,path.c_str(),32);
		_fontMap.insert(make_pair(path, font));
		return getFont(path);
	}
	return &mit->second;
}
