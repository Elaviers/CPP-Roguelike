#include "PropertySet.h"

#include "String.h"

#include <cstring> //for memcpy (hacky)

template <class T>
inline T findValue(const std::vector<Property<T>>& vector, const String& name) {
	for (auto it = vector.begin(); it != vector.end(); it++)
		if (it->getName() == name)
			it->getValue();

	return 0;
}


PropertySet::PropertySet()
{
}


PropertySet::~PropertySet()
{
}

void PropertySet::clear() {
	_chars.clear();
	_ints.clear();
	_floats.clear();
	_strings.clear();
}

void PropertySet::addToBuffer(std::vector<unsigned char>& buffer) {
	for (auto it = _chars.begin(); it != _chars.end(); it++)
		buffer.push_back((unsigned char)it->getValue());

	for (auto it = _ints.begin(); it != _ints.end(); it++) {
		buffer.push_back((it->getValue() >> 24) & 0xff );
		buffer.push_back((it->getValue() >> 16) & 0xff);
		buffer.push_back((it->getValue() >> 8) & 0xff);
		buffer.push_back(it->getValue() & 0xff);
	}
	for (auto it = _floats.begin(); it != _floats.end(); it++) { //This is not very portable.. rip
		unsigned char bytes[sizeof(float)];
		std::memcpy(bytes,&it->getValue(),sizeof(float));
		buffer.insert(buffer.end(), bytes, bytes + sizeof(float));
	}

	for (auto it = _strings.begin(); it != _strings.end(); it++) {
		size_t place = buffer.size() - 1; //Null char at end of buffer
		buffer.resize(buffer.size() + it->getValue().getLength()); //Enlarge buffer
		strcpy_s((char*)&buffer[place], it->getValue().getSize(), it->getValue().getData());

		/*for (auto i = it->getValue().begin(); i < it->getValue().end(); i++)
			buffer.push_back((unsigned char)*i);
		buffer.push_back(0); //null char for end*/
	}
}

void PropertySet::getFromBuffer(std::vector<unsigned char>::iterator& charit) {
	for (auto it = _chars.begin(); it != _chars.end(); it++) {
		*it = *charit;
		charit++;
	}

	for (auto it = _ints.begin(); it != _ints.end(); it++) {
		*it = *charit << 24;
		*it += *++charit << 16;
		*it += *++charit << 8;
		*it += *++charit;
		charit++;
	}

	for (auto it = _floats.begin(); it != _floats.end(); it++) {
		float f;

		unsigned char bytes[sizeof(float)];
		for (int i = 0; i < sizeof(float); i++) {
			bytes[i] = *charit;
			charit++;
		}

		std::memcpy(&f, bytes, sizeof(float));
		*it = f;
	}

	//Load strings here
}

bool PropertySet::getBool(const String& name) const {
	return findValue(_chars, name) == 0 ? false : true;
}
char PropertySet::getChar(const String& name) const {
	return findValue(_chars, name);
}
int PropertySet::getInt(const String& name) const {
	return findValue(_ints, name);
}
float PropertySet::getFloat(const String& name) const {
	return findValue(_floats, name);
}
const String PropertySet::getString(const String& name) const {
	return findValue(_strings, name);
}

void PropertySet::setBool(const String& name, bool value) {
	_chars.push_back(Property<char>(name, value ? 1 : 0));
}
void PropertySet::setChar(const String& name, char value) {
	_chars.push_back(Property<char>(name, value));
}
void PropertySet::setInt(const String& name, int value) {
	_ints.push_back(Property<int>(name, value));
}
void PropertySet::setFloat(const String& name, float value) {
	_floats.push_back(Property<float>(name, value));
}
void PropertySet::setString(const String& name, const String& value) {
	_strings.push_back(Property<String>(name, value));
}
