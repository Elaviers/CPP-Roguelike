#pragma once
#include "EntityContainer.h"
#include "EntityData.h"
#include "PropertySet.h"

#include <Engine/Vector2.h>

#define ID(ENTID) static uByte getID() { return ENTID; };

class Entity
{
protected:
	EntityContainer* _parent;

	virtual void loadBytes(const uByte* data) {};
public:
	Entity() {};
	virtual ~Entity();

	Vector2f position;

	void setParent(EntityContainer* container);

	static unsigned char getID() { return 255; }; //Override this
	static Entity* createClassForID(unsigned char id);

	//Virtual stuff
	virtual void init() {};
	virtual void update(float DeltaTime) {};
	virtual void render(Shader& Shader) {};

	//virtual unsigned char* getData() const { return 0; };
	//virtual void loadData(const EntityData* data) { position = Vector2f{ (float)data->x, (float)data->y }; loadBytes(data->data); };

	virtual void GetProperties(PropertySet&) const {};
	virtual void SetProperties(const PropertySet&) {};
};
