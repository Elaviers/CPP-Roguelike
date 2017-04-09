#pragma once
#include "Tile.h"

#include <Engine/Camera2D.h>
#include <Engine/Colour.h>
#include <Engine/EntityData.h>
#include <Engine/Texture.h>
#include <Engine/Vector2.h>
#include <vector>

class Level
{
private:
	std::vector<Tile> _tiles;
	std::vector<EntityData> _entData;
public:
	Level();
	~Level();

	Vector2 getSpawnPoint();
	Texture *tileSheet, *editorTileSheet;

	Tile* getData();

	void drawSprites(Camera2D&,int layer);
	void drawSprites(Camera2D&, int layer, Colour c);
	void drawEntitySprites();

	void addTile(const Tile&);
	void removeTile(const Tile&);

	void addEntityData(const EntityData&);
	void removeEntityData(const EntityData&);

	bool save(const char*);
	bool load(const char*);

	Tile* pointOverlaps(Vector2 point, int layer);
	Tile* rectOverlaps(Vector2 min, Vector2 max, int layer);
};
