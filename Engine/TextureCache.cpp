#include "TextureCache.h"

#include "ImageIO.h"
#include "String.h"
#include <iostream>

TextureCache::TextureCache() {
}

TextureCache::~TextureCache() {
}

Texture* TextureCache::getTexture(const char* path) {
	
	auto mit = textureMap.find(path);

	if (mit == textureMap.end()) {
		std::cout << "Caching texture " << path << std::endl;
		textureMap.insert(std::make_pair(path, ImageIO::loadPNG(path)));
		return getTexture(path);
	}
	return &mit->second;
}
