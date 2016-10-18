#include "Player.h"
#include <math.h>
#include <Engine/ResourceManager.h>

bool u, d, l, r;

void Player::init(int x,int y,int size,int crosshairSize,std::string texture, std::string texture1) {
	_crosshair.init(0, 0, (float)crosshairSize, (float)crosshairSize, false, texture);
	_crosshair.setOrigin(0,0);
	_pointer.init((float)x, (float)y, (float)size, (float)size, false, texture1);
	_pointer.setOrigin(0, 0);
	ResourceManager::getTexture("Game/Top Quality Textures/proj.png");//Cache projectile texture
}

void Player::update(float gameTime,float wheight) {
	SDL_GetMouseState(&mouseX, &mouseY);
	mouseY = (int)wheight - mouseY;

	if (_shooting && gameTime - _lastShot > fireRate) {
		_lastShot = gameTime;
		shoot();
	}
}

void Player::render(GLSLShading shader, Camera2D& cam, float frameTime) {
	//////////
	GLint textureLocation = shader.getUniformLocation("sTexture");
	glUniform1i(textureLocation, 0);

	GLint matLocation = shader.getUniformLocation("p");
	glUniformMatrix4fv(matLocation, 1, GL_FALSE, &(cam.getCameraMatrix()[0][0]));
	//////////Copied from Sprite.cpp's render calls to prevent getting recalled and be neat.

	_pointer.move(_moveX * moveSpeed * frameTime,_moveY * moveSpeed * frameTime);
	_pointer.setRotation(std::atan2(mouseY - _pointer.y, mouseX - _pointer.x) * 180 / (float)M_PI);
	_pointer.render();

	_crosshair.setPosition((float)mouseX, (float)mouseY);
	_crosshair.render();

	for (unsigned int i = 0; i < _projectiles.size(); i++) {
		_projectiles[i].render(frameTime);
	}

	glBindTexture(GL_TEXTURE_2D,0);
}

void  Player::shoot() {
	Projectile p;
	p.init(_pointer.x, _pointer.y, 64, "Game/Top Quality Textures/proj.png");
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