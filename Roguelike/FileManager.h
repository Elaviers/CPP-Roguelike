#pragma once
#include <fstream>
#include <string>
#include <vector>

struct StringPair {
	std::string Property, Value;
};

using namespace std;

namespace FileManager
{
	vector<StringPair> readFile(char* FilePath);

	bool readBool(vector<StringPair> Properties,string PropertyName);
	int readInt(vector<StringPair> Properties,string PropertyName);
}