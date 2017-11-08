#pragma once
#include "String.h"
#include <vector>

class IOManager
{
public:
	static bool readFileToBuffer(const char* path, std::vector<unsigned char> &buffer); //Reads a file from disk to an unsigned char vector

	static std::vector<String> getFilesInDirectory(const char * path, const char * extension);
};
