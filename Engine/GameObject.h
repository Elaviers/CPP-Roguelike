#pragma once

#include "RenderType.h"
#include "Shader.h"

class GameObject
{
public:
	GameObject() {};
	virtual ~GameObject() {};

	RenderTypes::RenderType RenderType;

	virtual void init() {};
	virtual void update() {};
	virtual void render(Shader& Shader, float DeltaTime) {};
};
