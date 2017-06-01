#pragma once
#include "Tile.h"

#include <Engine/Rect.h>
#include <vector>

class Entity;
class Shader;
class Texture;

class Level
{
private:
	std::vector<Tile> _tiles;
	std::vector<Entity*> _entities;

	int _tileSize;
public:
	Level();
	~Level();

	const std::vector<Tile> *tileData() const { return &_tiles; };
	const std::vector<Entity*> *entities() const { return &_entities; };
	void setTileSize(int tileSize) { _tileSize = tileSize; };
	const int getTileSize() { return _tileSize; };

	void addTile(const Tile&);
	void removeTile(signed char layer, signed char x, signed char y);
	void addEntity(Entity*);
	void removeEntity(const Vector2f&);

	bool save(const char*) const;
	bool load(const char*);

	void drawTiles(signed char maxLayer, bool startAtBeginning, const Rect_i&, const Texture&) const;
	void drawEntities(Shader&) const;
	void updateEntities(float deltaSeconds) const;
};
