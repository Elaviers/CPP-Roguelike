#include "FileManager.h"

using namespace std;

vector<StringPair> FileManager::readFile(char* Path)
{
	ifstream stream(Path);
	string str;

	if (!stream.is_open())return (vector<StringPair>)NULL;

	vector<StringPair> returnvalue;
	while (getline(stream, str)) {
		StringPair s;
		int i = str.find("=");
		s.Property = str.substr(0, i);
		s.Value = str.substr(i+1,str.back());
		returnvalue.push_back(s);
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