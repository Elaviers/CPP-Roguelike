#pragma once
#include "String.h"

template <class T>
class Register
{
	unsigned char	_id;
	String			_name;
protected:
	Register(unsigned char id, const String& name) : _id(id), _name(name) {};
public:
	virtual ~Register() {};
	virtual T* create() = 0;
	virtual const bool isType(const T*) = 0;

	const unsigned char getID() { return _id; };
	const String getName() { return _name; };
};

template <class Base,class T>
class FullRegister : public Register<Base> {
public:
	FullRegister(unsigned char id, const String& name) : Register(id,name) {};
	virtual ~FullRegister() {};

	virtual Base* create() { return new T; };

	virtual const bool isType(const Base* ptr) { return dynamic_cast<const T*>(ptr); };
};

class Entity;

typedef Register<Entity> EntityRegister;

template <class T>
using FullEntityRegister = FullRegister<Entity, T>;
