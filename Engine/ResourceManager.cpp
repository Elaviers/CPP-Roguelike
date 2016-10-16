#include "ResourceManager.h"

TextureCache ResourceManager::_tCache;

Texture ResourceManager::getTexture(std::string path) {
	return _tCache.getTexture(path);
}