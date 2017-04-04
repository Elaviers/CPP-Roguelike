#pragma once
#include "Texture.h"

#include <map>

class TextureCache
{
public:
	TextureCache();
	~TextureCache();

	Texture* getTexture(const std::string& path);
private:
	std::map<std::string, Texture> textureMap;
};
