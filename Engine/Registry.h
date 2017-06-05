#pragma once
#include "Register.h"

#include <map>

class EntityRegistry
{
private:
	static std::map<unsigned char, EntityRegister*> _registry;
public:
	template <class T>
	inline static void add(unsigned char id, const std::string& name) {
		_registry.insert(std::pair<unsigned char, EntityRegister*>(id, new FullEntityRegister<T>(id, name)));
	}

	static const std::string getNameOfID(unsigned char id);
	static Entity* createEntity(unsigned char id);

	static EntityRegister* getEntityRegister(const Entity*);
};

