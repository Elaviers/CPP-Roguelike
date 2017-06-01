#pragma once
#include "EntityRegister.h"

#include <map>

class EntityRegistry
{
private:
	static std::map<unsigned char, EntityRegisterBase*> _registry;
public:
	EntityRegistry();
	~EntityRegistry();

	static void init();

	template <class T>
	inline static void add(unsigned char id, const std::string& name) {
		_registry.insert(std::pair<unsigned char, EntityRegisterBase*>(id, new EntityRegister<T>(id, name)));
	}

	static const std::string getNameOfID(unsigned char id);
	static Entity* createEntity(unsigned char id);

	static EntityRegisterBase* getEntityRegister(const Entity*);
};

