#pragma once
#include <string>
#include "TextureCache.h"
class ResourceManager
{
public:
	static Texture getTexture(std::string path);
private:
	static TextureCache _tCache;
};