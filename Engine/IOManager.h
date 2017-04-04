#pragma once
#include <vector>

class IOManager
{
public:
	static bool readFileToBuffer(const std::string &path, std::vector<unsigned char> &buffer); //Reads a file from disk to an unsigned char vector

	static std::vector<std::string> getFilesInDirectory(const char * path, const char * extension);
};
