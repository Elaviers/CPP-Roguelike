#pragma once
#include <string>
#include <vector>
#include "Level.h"

struct StringPair {
	std::string Property, Value;
};

using namespace std;

namespace FileManager
{
	vector<StringPair> readFile(const char* FilePath);
	vector<Tile> readLevelFile(const char* FilePath, int);
	void writeLevelFile(std::vector<Tile> tiles, const char* path);

	bool readBool(vector<StringPair> Properties,string PropertyName);
	int readInt(vector<StringPair> Properties,string PropertyName);
}