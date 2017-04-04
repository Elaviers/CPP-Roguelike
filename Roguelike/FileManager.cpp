#include "FileManager.h"

#include <Engine/Utility.h>
#include <fstream>
#include <iostream>
#include <iterator>

const int CHAR_OFFSET = 132;

using namespace std;

namespace LevelFlags {
	enum LevelFlags {
		LAYER = 0,
		TILEID = 1,
		X = 2,
		ENTLAYER = 7
	};
}

void FileManager::readFile(const char* Path, vector<StringPair>& arr)
{
	ifstream stream(Path);
	string str;

	if (!stream.is_open())return;

	arr.clear();

	while (getline(stream, str)) {
		StringPair s;
		int i = (int)str.find("=");
		s.Property = str.substr(0, i);
		s.Value = str.substr(i + 1, str.length() - i);
		arr.push_back(s);
	}

	stream.close();
}

bool FileManager::readBool(const vector<StringPair>& arr, const string& name) {
	for (StringPair p : arr)
		if (p.Property == name && p.Value == "true")
			return true;
	return false;
}

int FileManager::readInt(const vector<StringPair>& arr, const string& name) {
	for (StringPair p : arr)
		if (p.Property == name)
			return stoi(p.Value);

	return -1;
}

void FileManager::readLevelFile(const char* Path, int unitSize, vector<Tile>& tileList, vector<EntityData>& entityList)
{
	ifstream stream(Path, ios::binary | ios::in);
	stream >> std::noskipws;

	if (!stream.is_open())return;

	std::vector<unsigned char>buffer((istream_iterator<unsigned char>(stream)), istream_iterator<unsigned char>());

	std::cout << "(FileManager) : Beginning load..." << endl;
	tileList.clear();
	entityList.clear();

	bool force = true;
	bool placeEntity = false;
	
	unsigned char currentEntID;
	int currentLayer, currentID, currentX;
	auto it = buffer.begin();
	while (it < buffer.end()) {
		if (*it < 8) {
			if (*it == LevelFlags::LAYER) {
				currentLayer = *++it - CHAR_OFFSET;
				placeEntity = false;
				force = true;
				//it++;
				std::cout << "layer " << currentLayer << '\n';
			}
			else if (*it == LevelFlags::ENTLAYER) {
				currentEntID = *++it;
				placeEntity = true;
				force = true;
				//it++;
				std::cout << "entity id " << (int)currentEntID << '\n';
			}

			if (!placeEntity && (force || *it == LevelFlags::TILEID)) {
				currentID = *++it - CHAR_OFFSET;
				force = true;
				//it++;
				std::cout << u8"├──id " << currentID << '\n';
			}
			if (force || *it == LevelFlags::X) {
				currentX = *++it - CHAR_OFFSET;
				force = false;
				it++;
				std::cout << u8"│  ├──x " << currentX << '\n';
			}
		}

		if (!placeEntity) {
			tileList.push_back(Tile { currentLayer, currentID, currentX * unitSize, (*it - CHAR_OFFSET) * unitSize });
			std::cout << u8"│  │  ├──y " << *it - CHAR_OFFSET << '\n';
			it++;
		}
		else {
			int data_len = 0;

			for (unsigned char* ch = &(*it) + 1; *ch != 0; ch++) data_len++;

			unsigned char* data;

			if (data_len > 0) {
				data = new unsigned char[data_len];
				for (int i = 0; i < data_len; i++)
					data[i] = *(&(*it) + 1 + i);
			}
			else data = NULL;

			entityList.push_back(EntityData{ currentEntID, data, Vector2 {currentX * unitSize, (*it - CHAR_OFFSET) * unitSize} });

			std::cout << u8"│  │  ├──y " << *it - CHAR_OFFSET << '\n';


			it += data_len + 2; //It's data_len + 2 because the iterator is before the data and it has to skip until it's passed the null char
		}
	}

	stream.close();
}

void FileManager::writeLevelFile(const std::vector<Tile>& tiles, const std::vector<EntityData>& entities, const char* path, int unitSize) {

	ofstream stream(path, ios::binary | ios::out);
	if (!stream.is_open())return;

	bool force = true;

	std::printf("(DEBUG) saved %d tiles\n", (int)tiles.size());

	vector<unsigned char> buffer;

	int currentLayer, currentIndex, currentX, currentY;
	for (Tile t : tiles) {
		//Values 0-7 are load flags
		if (force || t.layer != currentLayer) {
			buffer.push_back(LevelFlags::LAYER);//Flag : new Layer
			buffer.push_back(t.layer + CHAR_OFFSET);
			printf("push new layer: %d (%d)\n", t.layer + CHAR_OFFSET, t.layer);
			currentLayer = t.layer;
			force = true;
		}
		if (force || t.TileID != currentIndex) {
			if (!force)buffer.push_back(LevelFlags::TILEID);//Flag : new TileID
			buffer.push_back(t.TileID + CHAR_OFFSET);
			currentIndex = t.TileID;
			printf("push new ID: %d (%d)\n", t.TileID + CHAR_OFFSET, t.TileID);
			force = true;
		}
		if (force || t.x != currentX) {
			if (!force)buffer.push_back(LevelFlags::X);//Flag : new X value
			buffer.push_back(t.x / unitSize + CHAR_OFFSET);
			currentX = (int)t.x;
			printf("push new x: %d (%d)\n", t.x / unitSize + CHAR_OFFSET, t.x);
			force = true;
		}
		if (force || t.y != currentY) {
			buffer.push_back(t.y / unitSize + CHAR_OFFSET);
			currentY = (int)t.y;
			printf("push new y: %d (%d)\n", t.y / unitSize + CHAR_OFFSET, t.y);
			force = false;
		}
	}

	force = true;

	unsigned char currentID;
	currentX = currentY = 0;
	for (EntityData e : entities) {
		if (force || e.ID != currentID) {
			buffer.push_back(LevelFlags::ENTLAYER);
			buffer.push_back(e.ID);
			printf("push new entity layer: ID %d\n", e.ID);
			currentID = e.ID;
			force = true;
		}
		if (force || e.position.x != currentX) {
			if (!force)buffer.push_back(LevelFlags::X);//Flag : new X value
			buffer.push_back(e.position.x / unitSize + CHAR_OFFSET);
			currentX = e.position.x;
			printf("push new x: %d (%d)\n", e.position.x / unitSize + CHAR_OFFSET, e.position.x);
			force = true;
		}
		if (force || e.position.y != currentY) {
			buffer.push_back(e.position.y / unitSize + CHAR_OFFSET);
			currentY = e.position.y;

			if (e.data != NULL)
				for (int i = 0; e.data[i] != 0; i++)
					buffer.push_back(e.data[i]);

			buffer.push_back(0);
			printf("push new y: %d (%d)\n", e.position.y / unitSize + CHAR_OFFSET, e.position.y);
			force = false;
		}
	}

	stream.write((const char*)buffer.data(), sizeof(unsigned char) * buffer.size());
	stream.close();
}
