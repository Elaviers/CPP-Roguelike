#pragma once
#include "Types.h"

#include <string>
#include <vector>

class Property
{
protected:
	std::string name;
public:
	Property(std::string name) : name(name) {};
	virtual ~Property() = 0;

	virtual void addDataToBuffer(std::vector<uByte>*) = 0;
};

