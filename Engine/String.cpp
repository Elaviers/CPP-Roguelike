#include "String.h"

#include <cstring>

String::String() {
}

String::String(const char* str) {
	_size = strlen(str) + 1;
	_string = new char[_size];
	strcpy_s(_string, _size, str);
}

String::String(const String& str) {
	_size = str._size;
	_string = new char[_size];
	strcpy_s(_string, _size, str._string);
}

String::~String() {
	delete[] _string;
}

//--

String& String::operator--() {
	--_size;
	char* new_str = new char[_size];
	
	for (int i = 0; i < _size - 1; ++i)
		new_str[i] = _string[i];
	new_str[_size - 1] = '\0';

	delete[] _string;
	_string = new_str;

	return *this;
}

//=

String& String::operator=(const String& other) {
	delete[] _string;

	_size = other._size;
	_string = new char[_size];
	strcpy_s(_string, _size, other._string);

	return *this;
}

String& String::operator=(const char* other) {
	delete[] _string;
	_size = strlen(other) + 1;
	_string = new char[_size];
	strcpy_s(_string, _size, other);

	return *this;
}

//+=

String& String::operator+=(const String& other) {
	_size += other.getLength();

	char* new_str = new char[_size];
	strcpy_s(new_str, _size, _string);
	strcat_s(new_str, _size, other._string);

	delete[] _string;
	_string = new_str;

	return *this;
}

String& String::operator+=(const char* other) {
	_size += strlen(other);

	char* new_str = new char[_size];
	strcpy_s(new_str, _size, _string);
	strcat_s(new_str, _size, other);

	delete[] _string;
	_string = new_str;

	return *this;
}

String& String::operator+=(char other) {
	++_size;

	char* new_str = new char[_size];
	strcpy_s(new_str, _size, _string);

	delete[] _string;
	_string = new_str;
	_string[_size - 2] = other;
	_string[_size - 1] = '\0';

	return *this;
}

//==

bool String::operator==(const char *other) const {
	return strcmp(_string, other) == 0;
}

//<, >

bool String::operator<(const String& other) const {
	return _size < other._size;
}

bool String::operator>(const String& other) const {
	return _size > other._size;
}

//+

const String operator+(const char* a, const String& b) {
	String str(a);
	str += b;
	return str;
}

//Conversion

#include <cstdio>
//For snprintf

#define CONVERT_BODY(LEN, VAL, FORMAT) \
	char tostr[LEN]; \
	snprintf(tostr, LEN, FORMAT, VAL); \
	return String(tostr)

const String String::convert(char value) { CONVERT_BODY(5, value, "%d"); };
const String String::convert(int value) { CONVERT_BODY(12, value, "%d"); };
const String String::convert(float value) { CONVERT_BODY(16, value, "%f"); };
