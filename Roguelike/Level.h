#pragma once
#include "TileData.h"

#include <Engine/EntityData.h>
#include <vector>

class Level
{
private:
	std::vector<TileData> _tileData;
	std::vector<EntityData> _entData;
public:
	Level();
	~Level();
	const std::vector<TileData> *tileData() { return &_tileData; };
	const std::vector<EntityData> *entityData() { return &_entData; };

	void addTileData(const TileData&);
	void removeTileData(const TileData&);

	void addEntityData(const EntityData&);
	void removeEntityData(const EntityData&);

	bool save(const char*);
	bool load(const char*);
};
