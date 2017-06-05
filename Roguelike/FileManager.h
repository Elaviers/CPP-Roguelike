#pragma once
#include "Tile.h"

#include <string>
#include <vector>

class Entity;

struct StringPair {
	std::string Property, Value;
};

namespace FileManager
{	
	void readFile(const char* FilePath, std::vector<StringPair>& arr);
	bool readLevelFile(const char* FilePath, std::vector<Tile>& tileList, std::vector<Entity*>& entityList);
	bool writeLevelFile(const std::vector<Tile>& tiles, const std::vector<Entity*>&, const char* path);

	bool readBool(const std::vector<StringPair>& Properties,const std::string& PropertyName);
	int readInt(const std::vector<StringPair>& Properties,const std::string& PropertyName);
}
