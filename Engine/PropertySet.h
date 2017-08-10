#pragma once
#include "Property.h"

#include <vector>

class PropertySet
{
protected:
	std::vector<Property<char>> _chars;
	std::vector<Property<int>> _ints;
	std::vector<Property<float>> _floats;
	std::vector<Property<std::string>> _strings;

public:
	PropertySet();
	~PropertySet();

	void clear();
	void addToBuffer(std::vector<unsigned char>& buffer);
	void getFromBuffer(std::vector<unsigned char>::iterator&);

	const std::vector<Property<char>>& getChars() const { return _chars; };
	const std::vector<Property<int>>& getInts() const { return _ints; };
	const std::vector<Property<float>>& getFloats() const { return _floats; };
	const std::vector<Property<std::string>>& getStrings() const { return _strings; };

	bool getBool(const std::string& name) const;
	char getChar(const std::string& name) const;
	int getInt(const std::string& name) const;
	float getFloat(const std::string& name) const;
	const std::string getString(const std::string& name) const;

	void setBool(const std::string& name, bool value);
	void setChar(const std::string& name, char value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
	void setString(const std::string& name, const std::string& value);
};

