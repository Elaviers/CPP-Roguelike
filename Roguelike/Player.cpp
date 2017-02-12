#include "Player.h"
#include <math.h>
#include <Engine/ResourceManager.h>
#include <Engine/GUI.H>

bool u, d, l, r;
glm::vec2 MouseWorldPosition;

void Player::init(int x,int y,int size,int crosshairSize,std::string texture, std::string texture1) {
	_crosshair.init(0, 0, (float)crosshairSize, (float)crosshairSize, false, texture);
	_crosshair.setOrigin(0,0);
	_playerSprite.UVGridDivisions = 3;
	_playerSprite.init((float)x, (float)y, (float)size, (float)size, false, texture1);
	_playerSprite.setOrigin(0, -0.5f);
	ResourceManager::getTexture("Game/Textures/proj.png");//Cache projectile texture
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

	if(!_level->pointOverlaps(movex > 0 ? _playerSprite.x + 32 : _playerSprite.x - 32, _playerSprite.y,0))
		_playerSprite.move(movex, 0);

	if (!_level->pointOverlaps(_playerSprite.x, movey > 0 ? _playerSprite.y + 32 : _playerSprite.y - 32, 0))
	_playerSprite.move(0,movey);

	cam.setPosition(_playerSprite.x,_playerSprite.y);
	MouseWorldPosition = cam.screentoWorld(mouseX, mouseY);
	//_playerSprite.setRotation(std::atan2(MouseWorldPosition.y - _playerSprite.y, MouseWorldPosition.x - _playerSprite.x) * 180 / (float)M_PI);
	_playerSprite.render();

	shader.setMat4("projection",cam.getScreenMatrix());
	_crosshair.setPosition((float)mouseX, (float)mouseY);
	_crosshair.render();

	glBindTexture(GL_TEXTURE_2D,0);
}

void  Player::shoot() {
	Projectile p;
	_projectiles.push_back(p);
	_projectiles.back().init(_playerSprite.x,_playerSprite.y + 32, 64, std::atan2(MouseWorldPosition.y - _playerSprite.y, MouseWorldPosition.x - _playerSprite.x) * 180 / (float)M_PI,512, "Game/Textures/proj.png");
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

	_playerSprite.swapUVs(u&&l ? 4 : d&&l ? 5 : d&&r ? 6 : u&&r ? 7 : l ? 0 : d ? 1 : r ? 2 : u ? 3 : 1);
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

	_playerSprite.swapUVs(u&&l ? 4 : d&&l ? 5 : d&&r ? 6 : u&&r ? 7 : l ? 0 : d ? 1 : r ? 2 : u ? 3 : 1);
}

void Player::setPointerLocation(float x,float y) {
	_playerSprite.setPosition(x,y);
}