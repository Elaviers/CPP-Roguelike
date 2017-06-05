#pragma once
#include "Registry.h"
#include "Vector2.h"
#include <string>

class PropertySet;
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
	const std::string getName() const;

	//Virtual stuff
	virtual void init() {};
	virtual void update(float DeltaTime) {};
	virtual void render(Shader& Shader) {};

	virtual void GetProperties(PropertySet&) const {};
	virtual void SetProperties(const PropertySet&) {};
};
