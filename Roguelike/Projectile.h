#pragma once
#include <Engine/Entity.h>
#include <Engine/Shader.h>
#include <Engine/Sprite.h>
#include <Engine/Texture.h>
#include <Engine/Vector2.h>
#include <glm/vec2.hpp>

class Projectile : public Entity
{
private:
	Sprite _sprite;
	Vector2f _direction;
	float _size, _speed;
public:
	Projectile();
	~Projectile() {};

	void init(float x, float y, float size, float direction, float speed, const char* texture_path);
	void update(float DeltaTime) override;
	void render(Shader& s) override;
};
