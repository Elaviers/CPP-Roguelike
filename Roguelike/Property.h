#pragma once
#include "Types.h"

#include <string>
#include <vector>

template <class T>
class Property {
protected:
	std::string name;
	T value;
public:
	Property(const std::string& name) : name(name) {};
	Property(const std::string& name, const T& value) : name(name), value(value) {};
	virtual ~Property() {};
	////
	const std::string& getName() const { return name; };
	const T& getValue() const { return value; };
	////
	Property<T>& operator=(const T& other) { value = other; return *this; };
	Property<T>& operator+=(const T& other) { value += other; return *this; };

	//operator T() const { return value; }; //too confusing
};
