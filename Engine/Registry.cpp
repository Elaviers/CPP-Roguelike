#include "Registry.h"

std::map<unsigned char, EntityRegister*> EntityRegistry::_registry;

const std::string EntityRegistry::getNameOfID(unsigned char id) {
	auto it = _registry.find(id);

	if (it == _registry.end())
		return "None";

	return it->second->getName();
}

Entity* EntityRegistry::createEntity(unsigned char id) {
	auto it = _registry.find(id);

	if (it == _registry.end()) {
		std::printf("Can not create entity id %d!\n", id);
		return 0;
	}

	return it->second->create();
}

EntityRegister* EntityRegistry::getEntityRegister(const Entity* ptr) {
	for (auto it = _registry.begin(); it != _registry.end(); it++)
		if (it->second->isType(ptr))
			return it->second;

	return 0;
}
