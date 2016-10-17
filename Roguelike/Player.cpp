#include "Player.h"
#include "Game.h"
#include <math.h>
#include <Engine/ResourceManager.h>

int s;
bool u, d, l, r;

void Player::init(int x,int y,int size,std::string texture) {
	_crosshair.init(x, y, size, size, false, texture);
	_pointer.init(WIDTH / 2-64, HEIGHT / 2-64, 128, 128, false, "pointer.png");
	ResourceManager::getTexture("proj.png");
	s = size;
}

void Player::update(float gameTime) {
	SDL_GetMouseState(&mouseX, &mouseY);
	mouseY = HEIGHT-mouseY;

	if (_shooting && gameTime - _lastShot > fireRate) {
			_lastShot = gameTime;
			shoot();
	}
}

void Player::render(GLSLShading shader, Camera2D& cam, float frameTime) {
	GLint textureLocation = shader.getUniformLocation("sTexture");
	glUniform1i(textureLocation, 0);

	GLint matLocation = shader.getUniformLocation("p");
	glUniformMatrix4fv(matLocation, 1, GL_FALSE, &(cam.getCameraMatrix()[0][0]));

	_pointer.move(_moveX * moveSpeed * frameTime,_moveY * moveSpeed * frameTime);
	_pointer.rotation = std::atan2(mouseY - _pointer.y - _pointer.height/2, mouseX - _pointer.x - _pointer.width/2) * 180 / M_PI;
	_pointer.render();

	_crosshair.setPosition(mouseX-(s/2), mouseY-(s/2));
	_crosshair.render();

	for (int i = 0; i < _projectiles.size(); i++) {
		_projectiles[i].render(frameTime);
	}

	glBindTexture(GL_TEXTURE_2D,0);
}

void  Player::shoot() {
	Projectile p;
	p.init(_pointer.x + _pointer.width / 2 - 32, _pointer.y + _pointer.height / 2 - 32, 64, "proj.png");
	p.setDirection(_pointer.rotation);
	p.speed = 512;
	_projectiles.emplace(_projectiles.begin(), p);
}

void Player::keyUp(SDL_Event action) {
	switch (action.key.keysym.sym) {
	case SDLK_w:u = false; break;
	case SDLK_s:d = false; break;
	case SDLK_a:l = false; break;
	case SDLK_d:r = false; break;
	}

	_moveX = l ? (r ? 0 : -1) : r ? 1 : 0;
	_moveY = u ? (d ? 0 : 1) : d ? -1 : 0;
}

void Player::keyDown(SDL_Event action) {
	switch (action.key.keysym.sym) {
	case SDLK_w:u = true; break;
	case SDLK_s:d = true; break;
	case SDLK_a:l = true; break;
	case SDLK_d:r = true; break;
	}

	_moveX = l ? (r ? 0 : -1) : r ? 1 : 0;
	_moveY = u ? (d ? 0 : 1) : d ? -1 : 0;
}