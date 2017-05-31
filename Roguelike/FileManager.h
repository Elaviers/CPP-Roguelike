#pragma once
#include "Entity.h"
#include "Tile.h"

#include <string>
#include <vector>

struct StringPair {
	std::string Property, Value;
};

namespace FileManager
{	
	void readFile(const char* FilePath, std::vector<StringPair>& arr);
	void readLevelFile(const char* FilePath, std::vector<Tile>& tileList, std::vector<Entity*>& entityList);
	void writeLevelFile(const std::vector<Tile>& tiles, const std::vector<Entity*>&, const char* path);

	bool readBool(const std::vector<StringPair>& Properties,const std::string& PropertyName);
	int readInt(const std::vector<StringPair>& Properties,const std::string& PropertyName);
}
