#include "Projectile.h"

#include <math.h>

#include "Game.h"

Projectile::Projectile() {}

void Projectile::init(int x, int y, int s, std::string path) {
	_sprite.init(x, y, s, s, false, path);
}

void Projectile::render(float frameTime) {
	if (frameTime == 0)frameTime = 0.000001f;

	//RENDER WILL CRASH IF THE PROJECTILE IS NOT MOVED. DON'T ASK WHY, I DON'T KNOW.
	_sprite.move(std::cos(_sprite.rotation * M_PI / 180) * frameTime * speed, std::sin(_sprite.rotation * M_PI / 180) * frameTime * speed);
	_sprite.render();
}

void Projectile::setDirection(float a) {
	_sprite.rotation = a;
}