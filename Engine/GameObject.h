#pragma once
#include "Rect.h"
#include "RenderType.h"
#include "Shader.h"
#include "Vector2f.h"

class GameObject
{
public:
	GameObject() {};
	virtual ~GameObject() {};

	Vector2f position;
	Rect collision;

	RenderTypes::RenderType RenderType;

	virtual void init() {};
	virtual void update() {};
	virtual void render(Shader& Shader, float DeltaTime) {};
};
