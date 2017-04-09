#pragma once
#include "EntityContainer.h"
#include "EntityData.h"
#include "Vector2f.h"

class Entity
{
protected:
	EntityContainer* _parent;
public:
	Entity() {};
	virtual ~Entity();

	Vector2f position;

	void setParent(EntityContainer* container);

	virtual void init() {};
	virtual void update(float DeltaTime) {};
	virtual void render(Shader& Shader) {};

	virtual EntityData* getData() const { return 0; };
};
