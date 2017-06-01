#pragma once
#include "EntityContainer.h"
#include "EntityData.h"
#include "PropertySet.h"

#include <Engine/Vector2.h>

class Entity
{
protected:
	EntityContainer* _parent;
public:
	Entity();
	virtual ~Entity();

	Vector2f position;

	void setParent(EntityContainer* container);
	const unsigned char getID() const;
	const std::string getName() const;

	//Virtual stuff
	virtual void init() {};
	virtual void update(float DeltaTime) {};
	virtual void render(Shader& Shader) {};

	virtual void GetProperties(PropertySet&) const {};
	virtual void SetProperties(const PropertySet&) {};
};
