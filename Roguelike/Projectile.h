#pragma once

#include <Engine/Sprite.h>
#include <Engine/Texture.h>
#include <glm/glm.hpp>
#include <string>
#include <Engine/Shader.h>

class Projectile
{
private:
	Texture _texture;
	float _size, _direction, _speed;
	glm::vec2 _position;
public:
	Projectile();

	void init(float x, float y, float size,float direction,float speed, std::string);
	void render(float DeltaTime,Shader& s);
};