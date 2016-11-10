#include "FileManager.h"

#include <Engine/Utility.h>

#define CHAR_OFFSET (8 + 127 / 2)

using namespace std;

vector<StringPair> FileManager::readFile(const char* Path)
{
	ifstream stream(Path);
	string str;

	if (!stream.is_open())return (vector<StringPair>)NULL;

	vector<StringPair> returnvalue;
	while (getline(stream, str)) {
		StringPair s;
		int i = str.find("=");
		s.Property = str.substr(0, i);
		s.Value = str.substr(i+1,str.length() - i);
		returnvalue.push_back(s);
	}

	stream.close();
	return returnvalue;
}
#include <iostream>
vector<Tile> FileManager::readLevelFile(const char* Path,int unitSize)
{
	ifstream stream(Path);

	if (!stream.is_open())return (vector<Tile>)NULL;
	std::string str((istreambuf_iterator<char>(stream)), istreambuf_iterator<char>());

	Tile current;
	vector <Tile> returnvalue;

	int i = 0;
	bool first = true;
	while (i < str.length()) {
		if (str[i] < 8) {
			switch (str[i]) {
			case 0://New TileID
				current.TileID = str[++i] - CHAR_OFFSET;
			case 1://New X
				   //Comes here after case 0
				current.x = (str[++i] - CHAR_OFFSET) * 64;
				i++;
				break;
			case 2:
				returnvalue.back().flag = str[++i] - 8;//Subtract 8 instead of offset
				break;
			}
			continue;
		}

		current.y = (str[i++] - CHAR_OFFSET) * 64;
		returnvalue.push_back(current);

		if (current.flag > 0)
			current.flag = 0;
	}

	stream.close();
	return returnvalue;
}

bool FileManager::readBool(vector<StringPair> arr, string name) {
	for (StringPair p : arr)
		if (p.Property == name && p.Value == "true")
			return true;
	return false;
}

int FileManager::readInt(vector<StringPair> arr, string name) {
	for (StringPair p : arr)
		if (p.Property == name)
			return stoi(p.Value);

	return -1;
}