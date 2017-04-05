#pragma once
#include "EntityData.h"
#include "Rect.h"
#include "RenderType.h"
#include "Shader.h"
#include "Vector2f.h"

class Entity
{
public:
	Entity() {};
	virtual ~Entity() {};

	Vector2f position;
	Rect collision;

	RenderTypes::RenderType RenderType;

	virtual void init() {};
	virtual void update() {};
	virtual void render(Shader& Shader, float DeltaTime) {};

	virtual EntityData* getData() const { return NULL; };
};
