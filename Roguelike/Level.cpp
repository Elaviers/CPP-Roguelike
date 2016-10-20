#include "Level.h"



Level::Level()
{
}


Level::~Level()
{
}

using namespace FileManager;

void Level::init(const char* p) {
	_tiles = readLevelFile(p,64);
	_tex = ResourceManager::getTexture("Game/Top Quality Textures/tiles.png");

	_renderer.init();
}

SpawnPoint Level::getSpawnPoint() {
	SpawnPoint ret;
	for (Tile t : _tiles)
		if (t.flag == 's') {
			ret.x = t.x + 32;
			ret.y = t.y + 32;
		}
	return ret;
}

void Level::render(Shader s) {
	for (Tile t : _tiles) {
		if (t.TileID >= 0)_renderer.drawSprite(s, _tex, t.x, t.y, 64, 64, 0);

	}
}
