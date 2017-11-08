#include "ResourceManager.h"

TextureCache ResourceManager::_tCache;
FontCache ResourceManager::_fCache;

Texture ResourceManager::getTexture(const char* path) {
	return *_tCache.getTexture(path);
}

Texture* ResourceManager::getTextureRef(const char* path) {
	return _tCache.getTexture(path);
}

Font ResourceManager::getFont(const char* path) {
	return *_fCache.getFont(path);
}

Font* ResourceManager::getFontRef(const char* path) {
	return _fCache.getFont(path);
}

void ResourceManager::setFontLibrary(FT_Library& lib) {
	_fCache.setLibrary(lib);
}
