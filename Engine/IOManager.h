#pragma once
#include <vector>
class IOManager
{
public:
	static bool readFileToBuffer(std::string &path, std::vector<unsigned char> &buffer); //Reads a file from disk to an unsigned char vector
};

