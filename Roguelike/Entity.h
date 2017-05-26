#pragma once
#include "EntityContainer.h"
#include "EntityData.h"
#include "Property.h"

#include <Engine/Vector2f.h>

#define ID(ENTID) static uByte getID() { return ENTID; };

class Entity
{
protected:
	EntityContainer* _parent;
	std::vector<Property> _properties;

	virtual void loadBytes(const uByte* data) {};
public:
	Entity() {};
	virtual ~Entity();

	Vector2f position;

	void setParent(EntityContainer* container);

	EntityData getAllData(int gridSize);
	static unsigned char getID() { return 255; }; //Override this

	//Virtual stuff
	virtual void init() {};
	virtual void update(float DeltaTime) {};
	virtual void render(Shader& Shader) {};

	virtual unsigned char* getData() const { return 0; };
	virtual void loadData(const EntityData* data) { position = Vector2f{ (float)data->x, (float)data->y }; loadBytes(data->data); };

	static Entity* loadEntityFromData(const EntityData*, int gridSize);
};
