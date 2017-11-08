#pragma once
#include "Property.h"

#include <vector>

class PropertySet
{
protected:
	std::vector<Property<char>> _chars;
	std::vector<Property<int>> _ints;
	std::vector<Property<float>> _floats;
	std::vector<Property<String>> _strings;

public:
	PropertySet();
	~PropertySet();

	void clear();
	void addToBuffer(std::vector<unsigned char>& buffer);
	void getFromBuffer(std::vector<unsigned char>::iterator&);

	const std::vector<Property<char>>& getChars() const { return _chars; };
	const std::vector<Property<int>>& getInts() const { return _ints; };
	const std::vector<Property<float>>& getFloats() const { return _floats; };
	const std::vector<Property<String>>& getStrings() const { return _strings; };

	bool getBool(const String& name) const;
	char getChar(const String& name) const;
	int getInt(const String& name) const;
	float getFloat(const String& name) const;
	const String getString(const String& name) const;

	void setBool(const String& name, bool value);
	void setChar(const String& name, char value);
	void setInt(const String& name, int value);
	void setFloat(const String& name, float value);
	void setString(const String& name, const String& value);
};

