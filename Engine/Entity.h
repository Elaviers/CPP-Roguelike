#pragma once
#include "Registry.h"
#include "Vector2.h"

class PropertySet;
class String;
class Shader;

class Entity
{
protected:
	EntityRegister* _register;
public:
	Entity();
	virtual ~Entity();

	Vector2f position;

	const unsigned char getID() const;
	const String getName() const;

	//Virtual stuff
	virtual void init() {};
	virtual void update(float DeltaTime) {};
	virtual void render(Shader& Shader) {};

	virtual void GetProperties(PropertySet&) const {};
	virtual void SetProperties(const PropertySet&) {};
};
