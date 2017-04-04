#include "IOManager.h"

#include "ErrorHandling.h"

#include <fstream>
#include <windows.h>

bool IOManager::readFileToBuffer(const std::string &location, std::vector<unsigned char> &buffer) {
	std::ifstream file(location, std::ios::binary);
	if (file.fail()) {
		perror(location.c_str());
		return false;
	}

	file.seekg(0, std::ios::end);
	int fileSize = (int)file.tellg();
	file.seekg(0, std::ios::beg);

	//Subtract header size
	fileSize -= (int)file.tellg();

	buffer.resize(fileSize);
	file.read((char *)&(buffer[0]), fileSize);
	file.close();

	return true;
}

std::vector<std::string> IOManager::getFilesInDirectory(const char* path,const char* extension) {
	std::vector<std::string> ret;

	std::string fullPath = path + std::string("\\*.") + extension;

	WIN32_FIND_DATA data;
	HANDLE handle = FindFirstFile(fullPath.c_str(), &data);
	if (handle != INVALID_HANDLE_VALUE) {
		do {
			ret.push_back(data.cFileName);
		} while (FindNextFile(handle, &data));
		FindClose(handle);
	}

	return ret;
}
