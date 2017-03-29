#include <iostream>
#include "TextureCache.h"
#include "ImageIO.h"

TextureCache::TextureCache() {
}

TextureCache::~TextureCache() {
}

Texture* TextureCache::getTexture(const std::string& path) {
	
	auto mit = textureMap.find(path);

	if (mit == textureMap.end()) {
		std::cout << "Caching texture " << path << std::endl;
		textureMap.insert(make_pair(path, ImageIO::loadPNG(path)));
		return getTexture(path);
	}
	return &mit->second;
}