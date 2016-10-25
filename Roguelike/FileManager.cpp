#include "FileManager.h"

#include <Engine/Utility.h>

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
	string str;

	if (!stream.is_open())return (vector<Tile>)NULL;

	vector<Tile> returnvalue;
	while (getline(stream, str)) {
		if (str.length() > 0 && str[0] != '|') {
			vector<string> elements;
			Utility::splitString(str, ' ', elements);
			if (elements.size() >= 3) {
				for (int s = 0; s < elements.size(); s++)
					printf("%s | ", elements[s].c_str());
				printf("\n");

				Tile t;
				t.TileID = stoi(elements[0].c_str());
				t.x = unitSize * stoi(elements[1].c_str());
				t.y = unitSize * stoi(elements[2].c_str());
				if (elements.size() >= 4)
					t.flag = elements[3][0];
				else t.flag = 0;

				returnvalue.push_back(t);
			}
		}
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