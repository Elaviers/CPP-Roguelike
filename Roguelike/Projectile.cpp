#include "Projectile.h"

#include "GameData.h"

#include <bass.h>
#include <Engine/Constants.h>
#include <Engine/SpriteRenderer.h>
#include <Engine/ResourceManager.h>
#include <math.h>

Projectile::Projectile() { }

void Projectile::init(float x, float y, float s, float direction, float speed, std::string path) {
	position = Vector2f{ x,y };
	_size = s;
	_direction = direction * mathConstants::pi / 180;
	_speed = speed;
	_texture = ResourceManager::getTexture(path);

	static HSTREAM shootSound = BASS_StreamCreateFile(FALSE, "Game/Audio/Pop.wav", 0, 0, 0);
	BASS_ChannelPlay(shootSound, true);
}

void Projectile::update(float deltaTime) {
	position.x += std::cos(_direction) * deltaTime * _speed;
	position.y += std::sin(_direction) * deltaTime * _speed;

	if (GameData::level->pointOverlaps(position + Vector2f{std::cos(_direction) * _size / 2, std::sin(_direction) * _size / 2}, 0))
		delete this;
}

void Projectile::render(Shader& shader) {
	SpriteRenderer::drawSprite(shader, _texture, position.x - _size / 2, position.y - _size / 2, _size, _size, _direction);
}
