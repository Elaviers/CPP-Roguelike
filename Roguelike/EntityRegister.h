#pragma once
#include "Entity.h"

#include <string>

class EntityRegisterBase
{
private:
	unsigned char _id;
	std::string _name;
public:
	EntityRegisterBase(unsigned char id, const std::string& name) : _id(id), _name(name) {};
	virtual ~EntityRegisterBase() {};
	virtual Entity* createEntity() = 0;
	virtual const bool isType(const Entity*) = 0;

	const unsigned char getID() { return _id; };
	const std::string getName() { return _name; };
};

template <class T>
class EntityRegister : public EntityRegisterBase {
public:
	EntityRegister(unsigned char id, const std::string& name) : EntityRegisterBase(id,name) {};
	virtual ~EntityRegister() {};

	virtual Entity* createEntity() { return new T; };

	virtual const bool isType(const Entity* ptr) { return dynamic_cast<const T*>(ptr); };
};


