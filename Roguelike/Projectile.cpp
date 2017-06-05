#include "Projectile.h"

#include "World.h"

#include <bass.h>
#include <Engine/Constants.h>
#include <Engine/SpriteRenderer.h>
#include <Engine/ResourceManager.h>
#include <math.h>

#include <Engine/LineRenderer.h>

Projectile::Projectile() { }

void Projectile::init(float x, float y, float s, float direction, float speed, std::string path) {
	position = Vector2f{ x,y };
	_size = s;
	_direction = Vector2f(std::cos(direction * mathConstants::pi_f / 180), std::sin(direction * mathConstants::pi_f / 180));
	_speed = speed;
	_sprite.init(x, y, s, s, false, path);
	_sprite.setOrigin(0,0);
	_sprite.rotation = direction;

	static HSTREAM shootSound = BASS_StreamCreateFile(FALSE, "Game/Audio/Pop.wav", 0, 0, 0);
	BASS_ChannelPlay(shootSound, true);
}

void Projectile::update(float deltaTime) {
	position.x += _direction.x * deltaTime * _speed;
	position.y += _direction.y * deltaTime * _speed;

	_sprite.setPosition(position.x,position.y);

	if (Tile::pointOverlaps(*World::tileData(), 64, 0, (int)(position.x + _direction.x * _size / 4), (int)(position.y + _direction.y * _size / 4))) {
		World::removeEntity(this);
		delete this;
	}
}

void Projectile::render(Shader& shader) {
	_sprite.render();
}
