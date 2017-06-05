#pragma once
#include "Tile.h"

#include <Engine/Rect.h>
#include <vector>

class Entity;
class Shader;
class Texture;

class World
{
private:
	static std::vector<Tile> _tiles;
	static std::vector<Entity*> _entities;

	static int _tileSize;

	static std::vector<Entity*>::iterator _iterator;
public:
	static const std::vector<Tile> *tileData() { return &_tiles; };
	static const std::vector<Entity*> *entities() { return &_entities; };
	static void setTileSize(int tileSize) { _tileSize = tileSize; };
	static const int getTileSize() { return _tileSize; };

	static void addTile(const Tile&);
	static void removeTile(signed char layer, signed char x, signed char y);
	static void addEntity(Entity*, bool sort = false);
	static void removeEntity(Entity*);
	static void removeEntityAtPosition(const Vector2f&);

	static bool save(const char*);
	static bool load(const char*);

	static void drawTiles(signed char maxLayer, bool startAtBeginning, const Rect_i&, const Texture&);
	static void drawEntities(Shader&);
	static void updateEntities(float deltaSeconds);
};
