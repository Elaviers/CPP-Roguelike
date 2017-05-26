#include "FileManager.h"
#include "Types.h"

#include <Engine/Utility.h>
#include <fstream>
#include <iostream>
#include <iterator>

const unsigned char CHAR_OFFSET = 132;

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

void FileManager::readLevelFile(const char* Path, vector<TileData>& tileList, vector<EntityData>& entityList)
{
	ifstream stream(Path, ios::binary | ios::in);
	stream >> std::noskipws;

	if (!stream.is_open())return;

	std::vector<uByte>buffer((istream_iterator<unsigned char>(stream)), istream_iterator<unsigned char>());

	std::cout << "(FileManager) : Beginning load..." << endl;
	tileList.clear();
	entityList.clear();

	bool force = true;
	bool placeEntity = false;

	unsigned char currentEntID, currentID;
	signed char currentLayer, currentX;

	auto it = buffer.begin();
	while (it < buffer.end()) {
		if (*it < 8) {
			if (*it == LevelFlags::LAYER) {
				currentLayer = *++it - CHAR_OFFSET;
				placeEntity = false;
				force = true;
				//it++;
				std::cout << "layer " << (int)currentLayer << '\n';
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
				std::cout << u8"├──id " << (int)currentID << '\n';
			}
			if (force || *it == LevelFlags::X) {
				currentX = *++it - CHAR_OFFSET;
				force = false;
				it++;
				std::cout << u8"│  ├──x " << (int)currentX << '\n';
			}
		}

		if (!placeEntity) {
			tileList.push_back(TileData{ currentLayer, currentID, currentX, (*it - CHAR_OFFSET) });
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

			entityList.push_back(EntityData{ currentEntID, currentX, (signed char)(*it - CHAR_OFFSET), data });

			std::cout << u8"│  │  ├──y " << *it - CHAR_OFFSET << '\n';


			it += data_len + 2; //It's data_len + 2 because the iterator is before the data and it has to skip until it's passed the null char
		}
	}

	stream.close();
}

void FileManager::writeLevelFile(const std::vector<TileData>& tiles, const std::vector<EntityData>& entities, const char* path) {

	ofstream stream(path, ios::binary | ios::out);
	if (!stream.is_open())return;

	bool force = true;
	vector<unsigned char> buffer;

	signed char currentLayer;
	unsigned char currentID;
	signed char currentX, currentY;

	for (TileData t : tiles) {
		//Values 0-7 are load flags
		if (force || t.layer != currentLayer) {
			buffer.push_back(LevelFlags::LAYER);//Flag : new Layer
			buffer.push_back(t.layer + CHAR_OFFSET);
			printf("push new layer: %d (%d)\n", t.layer + CHAR_OFFSET, t.layer);
			currentLayer = t.layer;
			force = true;
		}
		if (force || t.id != currentID) {
			if (!force)buffer.push_back(LevelFlags::TILEID);//Flag : new TileID
			buffer.push_back(t.id + CHAR_OFFSET);
			currentID = t.id;
			printf("push new ID: %d (%d)\n", t.id + CHAR_OFFSET, t.id);
			force = true;
		}
		if (force || t.x != currentX) {
			if (!force)buffer.push_back(LevelFlags::X);//Flag : new X value
			buffer.push_back((unsigned char)t.x + CHAR_OFFSET);
			currentX = t.x;
			printf("push new x: %d (%d)\n", (unsigned char)t.x + CHAR_OFFSET, t.x);
			force = true;
		}
		if (force || t.y != currentY) {
			buffer.push_back((unsigned char)t.y + CHAR_OFFSET);
			currentY = t.y;
			printf("push new y: %d (%d)\n", (unsigned char)t.y + CHAR_OFFSET, t.y);
			force = false;
		}
	}

	force = true;

	currentX = currentY = currentID = 0;
	for (EntityData e : entities) {
		if (force || e.ID != currentID) {
			buffer.push_back(LevelFlags::ENTLAYER);
			buffer.push_back(e.ID);
			printf("push new entity layer: ID %d\n", e.ID);
			currentID = e.ID;
			force = true;
		}
		if (force || e.x != currentX) {
			if (!force)buffer.push_back(LevelFlags::X);//Flag : new X value
			buffer.push_back((unsigned char)e.x + CHAR_OFFSET);
			currentX = e.x;
			printf("push new x: %d (%d)\n", (unsigned char)e.x + CHAR_OFFSET, e.x);
			force = true;
		}
		if (force || e.y != currentY) {
			buffer.push_back((unsigned char)e.y + CHAR_OFFSET);
			currentY = e.y;

			if (e.data != NULL)
				for (int i = 0; e.data[i] != 0; i++)
					buffer.push_back(e.data[i]);

			buffer.push_back(0);
			printf("push new y: %d (%d)\n", (unsigned char)e.y + CHAR_OFFSET, e.y);
			force = false;
		}
	}

	stream.write((const char*)buffer.data(), sizeof(unsigned char) * buffer.size());
	stream.close();

	std::printf("(DEBUG) saved %d tiles\n", (int)tiles.size());
}
