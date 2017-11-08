#pragma once
#include "Register.h"
#include <map>

class String;

class EntityRegistry
{
	static std::map<unsigned char, EntityRegister*> _registry;

public:
	template <class T>
	inline static void add(unsigned char id, const String& name) {
		_registry.insert(std::pair<unsigned char, EntityRegister*>(id, new FullEntityRegister<T>(id, name)));
	}

	static const String getNameOfID(unsigned char id);
	static Entity* createEntity(unsigned char id);

	static EntityRegister* getEntityRegister(const Entity*);
};

