#pragma once
#include "FontCache.h"
#include "TextureCache.h"

class ResourceManager
{
public:
	static Texture getTexture(const char* path);//Loads or caches a texture from path
	static Texture* getTextureRef(const char* path);
	
	static Font getFont(const char* path);
	static Font* getFontRef(const char* path);
	static void setFontLibrary(FT_Library& library);
private:
	static TextureCache _tCache;
	static FontCache _fCache;
};
