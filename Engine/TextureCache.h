#pragma once
#include "Texture.h"
#include <map>

class String;

class TextureCache
{
public:
	TextureCache();
	~TextureCache();

	Texture* getTexture(const char* path);
private:
	std::map<String, Texture> textureMap;
};
