#include "Level.h"



Level::Level()
{
}


Level::~Level()
{
}

void Level::init(const char* p) {
	_tiles = FileManager::readLevelFile(p,64);
	_tex = ResourceManager::getTexture("Game/Textures/tiles.png");
}

SpawnPoint Level::getSpawnPoint() {
	SpawnPoint ret;
	for (Tile t : _tiles)
		if (t.flag == 's') {
			ret.x = (int)t.x + 32;
			ret.y = (int)t.y + 32;
		}
	return ret;
}

void Level::render(Shader s) {
	for (Tile t : _tiles)
		if (t.TileID >= 0)SpriteRenderer::drawSprite(_tex, t.x, t.y, 64, 64, 0, 8,t.TileID);

}
