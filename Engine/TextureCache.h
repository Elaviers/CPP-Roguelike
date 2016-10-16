#pragma once
#include <map>
#include "Texture.h"
class TextureCache
{
public:
	TextureCache();
	~TextureCache();

	Texture getTexture(std::string path);
private:
	std::map<std::string, Texture> textureMap;
};