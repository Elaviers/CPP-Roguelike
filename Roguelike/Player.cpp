#include "Player.h"
#include <math.h>
#include <Engine/ResourceManager.h>

bool u, d, l, r;
glm::vec2 MouseWorldPosition;

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

void Player::render(Camera2D& cam, float frameTime,Shader& shader) {
	float movex = _moveX * moveSpeed * frameTime;
	float movey = _moveY * moveSpeed * frameTime;

	for (unsigned int i = 0; i < _projectiles.size(); i++) {
		_projectiles[i].render(frameTime,shader);
	}

	shader.set2f("UVOffset", 0, 0); 
	shader.setMat4("transform",glm::mat4());

	_pointer.move(movex, movey);
	cam.setPosition(_pointer.x,_pointer.y);

	MouseWorldPosition = cam.screentoWorld(mouseX, mouseY);
	_pointer.setRotation(std::atan2(MouseWorldPosition.y - _pointer.y, MouseWorldPosition.x - _pointer.x) * 180 / (float)M_PI);
	_pointer.render();

	shader.setMat4("projection",cam.getScreenMatrix());
	_crosshair.setPosition((float)mouseX, (float)mouseY);
	_crosshair.render();

	glBindTexture(GL_TEXTURE_2D,0);
}

void  Player::shoot() {
	Projectile p;
	_projectiles.push_back(p);
	_projectiles.back().init(_pointer.x,_pointer.y, 64,_pointer.rotation,512, "Game/Top Quality Textures/proj.png");
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

void Player::setPointerLocation(float x,float y) {
	_pointer.setPosition(x,y);
}