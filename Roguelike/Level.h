#pragma once
#include "Entity.h"
#include "Tile.h"

#include <vector>

class Level
{
private:
	std::vector<Tile> _tiles;
	std::vector<Entity*> _entities;
public:
	Level();
	~Level();
	const std::vector<Tile> *tileData() { return &_tiles; };
	const std::vector<Entity*> *entities() { return &_entities; };

	void addTile(const Tile&);
	void removeTile(signed char layer, signed char x, signed char y);

	void addEntity(Entity*);
	void removeEntity(const Vector2f&);

	bool save(const char*);
	bool load(const char*);
};
