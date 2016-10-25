#include <math.h>
#include "Projectile.h"
#include "Game.h"

Projectile::Projectile() {}

void Projectile::init(float x, float y,float s,float direction,float speed, std::string path) {
	_position = glm::vec2(x,y);
	_size = s;
	_direction = direction;
	_speed = speed;
	_texture = ResourceManager::getTexture(path);
}

void Projectile::render(float frameTime,Shader& shader) {
	_position.x += (float)std::cos(_direction * M_PI / 180) * frameTime * _speed;
	_position.y += (float)std::sin(_direction * M_PI / 180) * frameTime * _speed;

	SpriteRenderer::drawSprite(shader,_texture, _position.x - _size/2, _position.y - _size/2,_size,_size,_direction * M_PI/180);
}