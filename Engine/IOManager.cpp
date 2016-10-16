#include "IOManager.h"
#include "ErrorHandling.h"
#include <fstream>

bool IOManager::readFileToBuffer(std::string &location, std::vector<unsigned char> &buffer) {
	std::ifstream file(location,std::ios::binary);
	if (file.fail()) {
		perror(location.c_str());
		return false;
	}
	
	file.seekg(0,std::ios::end);
	int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	//Subtract header size
	fileSize -= file.tellg();

	buffer.resize(fileSize);
	file.read((char *)&(buffer[0]),fileSize);
	file.close();

	return true;
}