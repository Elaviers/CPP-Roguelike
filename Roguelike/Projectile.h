#pragma once
#include <Engine/Entity.h>
#include <Engine/Shader.h>
#include <Engine/Sprite.h>
#include <Engine/Texture.h>
#include <glm/vec2.hpp>
#include <string>

class Projectile : public Entity
{
private:
	Texture _texture;
	float _size, _direction, _speed;
public:
	Projectile();
	~Projectile() {};

	void init(float x, float y, float size,float direction,float speed, std::string);
	void update(float DeltaTime) override;
	void render(Shader& s) override;
};
