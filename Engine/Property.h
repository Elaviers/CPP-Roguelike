#pragma once
#include <vector>

class String;

template <class T>
class Property {
protected:
	String name;
	T value;
public:
	Property(const String& name) : name(name) {};
	Property(const String& name, const T& value) : name(name), value(value) {};
	virtual ~Property() {};
	////
	const String& getName() const { return name; };
	const T& getValue() const { return value; };
	////
	Property<T>& operator=(const T& other) { value = other; return *this; };
	Property<T>& operator+=(const T& other) { value += other; return *this; };
};
