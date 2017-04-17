#pragma once
#include "Level.h"

#include <string>
#include <vector>

struct StringPair {
	std::string Property, Value;
};

namespace FileManager
{	
	void readFile(const char* FilePath, std::vector<StringPair>& arr);
	void readLevelFile(const char* FilePath, std::vector<TileData>& tileList, std::vector<EntityData>& entityList);
	void writeLevelFile(const std::vector<TileData>& tiles, const std::vector<EntityData>&, const char* path);

	bool readBool(const std::vector<StringPair>& Properties,const std::string& PropertyName);
	int readInt(const std::vector<StringPair>& Properties,const std::string& PropertyName);
}
