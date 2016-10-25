#pragma once
#include <string>
#include "TextureCache.h"
class ResourceManager
{
public:
	static Texture getTexture(std::string path);//Loads or caches a texture from path
private:
	static TextureCache _tCache;
};