#include "ResourceManager.h"

TextureCache ResourceManager::_tCache;
FontCache ResourceManager::_fCache;

Texture ResourceManager::getTexture(const std::string& path) {
	return *_tCache.getTexture(path);
}

Texture* ResourceManager::getTextureRef(const std::string& path) {
	return _tCache.getTexture(path);
}

Font ResourceManager::getFont(const std::string& path) {
	return *_fCache.getFont(path);
}

Font* ResourceManager::getFontRef(const std::string& path) {
	return _fCache.getFont(path);
}

void ResourceManager::setFontLibrary(FT_Library& lib) {
	_fCache.setLibrary(lib);
}
