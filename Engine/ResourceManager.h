#pragma once
#include "FontCache.h"
#include "TextureCache.h"

#include <string>

class ResourceManager
{
public:
	static Texture getTexture(const std::string& path);//Loads or caches a texture from path
	static Texture* getTextureRef(const std::string& path);
	
	static Font getFont(const std::string& path);
	static Font* getFontRef(const std::string& path);
	static void setFontLibrary(FT_Library& library);
private:
	static TextureCache _tCache;
	static FontCache _fCache;
};
