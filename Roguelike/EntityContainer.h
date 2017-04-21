#pragma once
#include <vector>

class Entity;
class Shader;

class EntityContainer
{
private:
	std::vector<Entity*> _entities, _add, _delete;
	bool _updating;
public:
	EntityContainer();
	~EntityContainer();

	void addEntity(Entity* e);
	void removeEntity(Entity* e);

	void update(float DeltaTime), render(Shader&);
};
