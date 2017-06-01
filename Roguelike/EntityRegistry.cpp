#include "EntityRegistry.h"

std::map<unsigned char, EntityRegisterBase*> EntityRegistry::_registry;

EntityRegistry::EntityRegistry()
{
	printf("LOL INIT\n");
}


EntityRegistry::~EntityRegistry()
{
}

const std::string EntityRegistry::getNameOfID(unsigned char id) {
	auto it = _registry.find(id);

	if (it == _registry.end())
		return "None";

	return it->second->getName();
}
Entity* EntityRegistry::createEntity(unsigned char id) {
	auto it = _registry.find(id);

	if (it == _registry.end()) {
		std::printf("Can not create entity id %d!\n",id);
		return 0;
	}

	return it->second->createEntity();
}

EntityRegisterBase* EntityRegistry::getEntityRegister(const Entity* ptr) {
	for (auto it = _registry.begin(); it != _registry.end(); it++)
		if (it->second->isType(ptr))
			return it->second;

	return 0;
}

#include "SpawnPoint.h"
#include "LevelConnector.h"

void EntityRegistry::init() {
	add<SpawnPoint>(0, "Spawn Point");
	add<LevelConnector>(1, "Level Connector");
}
