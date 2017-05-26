#pragma once
#include "EntityData.h"
#include "TileData.h"

#include <vector>

class LevelData
{
private:
	std::vector<TileData> _tileData;
	std::vector<EntityData> _entData;
public:
	LevelData();
	~LevelData();
	const std::vector<TileData> *tileData() { return &_tileData; };
	const std::vector<EntityData> *entityData() { return &_entData; };

	void addTileData(const TileData&);
	void removeTileData(const TileData&);

	void addEntityData(const EntityData&);
	void removeEntityData(const EntityData&);

	bool save(const char*);
	bool load(const char*);
};
