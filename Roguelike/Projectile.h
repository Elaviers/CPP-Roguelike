#pragma once

#include <Engine/Sprite.h>
#include <Engine/Camera2D.h>

class Projectile
{
private:
	Sprite _sprite;
public:
	float speed;

	Projectile();

	void init(float x, float y, float size, std::string);
	void setDirection(float Angle);
	void render(float DeltaTime);
};