#pragma once
#include <vector>
static class IOManager
{
public:
	static bool readFileToBuffer(std::string &path, std::vector<unsigned char> &buffer);
};

