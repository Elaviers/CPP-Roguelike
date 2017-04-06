#include <math.h>
#include <Engine/Constants.h>
#include "Projectile.h"

#include <bass.h>
#include <Engine/SpriteRenderer.h>
#include <Engine/ResourceManager.h>

Projectile::Projectile() { }

void Projectile::init(float x, float y,float s,float direction,float speed, std::string path) {
	position = Vector2f{x,y};
	_size = s;
	_direction = direction;
	_speed = speed;
	_texture = ResourceManager::getTexture(path);

	static HSTREAM shootSound = BASS_StreamCreateFile(FALSE, "Game/Audio/Pop.wav", 0, 0, 0);
	BASS_ChannelPlay(shootSound, true);
}

void Projectile::render(Shader& shader, float deltaTime) {
	position.x += (float)std::cos(_direction * mathConstants::pi / 180) * deltaTime * _speed;
	position.y += (float)std::sin(_direction * mathConstants::pi / 180) * deltaTime * _speed;

	SpriteRenderer::drawSprite(shader,_texture, position.x - _size/2, position.y - _size/2,_size,_size,_direction);
}
