#include "Player.h"
#include <math.h>
#include <Engine/ResourceManager.h>
#include <Engine/GUI.H>

#include "Game.h"

#include <iostream>

#include "GameManager.h"

bool u, d, l, r;

void Player::init(int x,int y,int size,int crosshairSize,std::string texture, std::string texture1) {
	_crosshair.init(0, 0, (float)crosshairSize, (float)crosshairSize, false, texture);
	_crosshair.setOrigin(0,0);
	_playerSprite.UVGridDivisions = 3;
	_playerSprite.init((float)x, (float)y, (float)size, (float)size, false, texture1);
	_playerSprite.setOrigin(0, -0.5f);
	ResourceManager::getTexture("Game/Textures/proj.png");//Cache projectile texture
}

void Player::update() {
	if (_shooting && GameManager::runTime - _lastShot > fireRate) {
		_lastShot = GameManager::runTime;
		shoot();
	}
}

void Player::render(Shader& shader,float frameTime) {
	float movex = _moveX * moveSpeed * frameTime;
	float movey = _moveY * moveSpeed * frameTime;

	for (unsigned int i = 0; i < _projectiles.size(); i++) {
		_projectiles[i].render(frameTime,shader);
	}

	shader.set2f("UVOffset", 0, 0); 
	shader.setMat4("transform",glm::mat4());

	if (movex != 0 /*?
		!(GameManager::level->pointOverlaps(_playerSprite.getCorner(CornerEnum::TOP_RIGHT), 0) || GameManager::level->pointOverlaps(_playerSprite.getCorner(CornerEnum::BOTTOM_RIGHT), 0))
		: movex < 0 ?
		!(GameManager::level->pointOverlaps(_playerSprite.getCorner(CornerEnum::TOP_LEFT), 0)  || GameManager::level->pointOverlaps(_playerSprite.getCorner(CornerEnum::BOTTOM_LEFT), 0))
		: false*/) {

		_playerSprite.move(movex, 0);
	}

	/*if (movex > 0)
		std::cout << "x:" << _playerSprite.x << " y:" << _playerSprite.y << " top-left:" << _playerSprite.getCorner(CornerEnum::TOP_LEFT).x << "," << _playerSprite.getCorner(CornerEnum::TOP_LEFT).y <<
		" bottom-right:" << _playerSprite.getCorner(CornerEnum::BOTTOM_RIGHT).x << "," << _playerSprite.getCorner(CornerEnum::BOTTOM_RIGHT).y << std::endl;
	*/

	if (movey != 0 /*?
		!(GameManager::level->pointOverlaps(_playerSprite.getCorner(CornerEnum::TOP_LEFT), 0) || GameManager::level->pointOverlaps(_playerSprite.getCorner(CornerEnum::TOP_RIGHT), 0))
		: movey < 0 ?
		!(GameManager::level->pointOverlaps(_playerSprite.getCorner(CornerEnum::BOTTOM_LEFT), 0) || GameManager::level->pointOverlaps(_playerSprite.getCorner(CornerEnum::BOTTOM_RIGHT), 0))
		: false*/) {

		_playerSprite.move(0, movey);
	}

	GameManager::camera->setPosition(_playerSprite.x,_playerSprite.y);

	_playerSprite.render();

	shader.setMat4("projection",GameManager::camera->getScreenMatrix());
	_crosshair.setPosition((float)GameManager::mousePosition.x, (float)GameManager::mousePosition.y);
	_crosshair.render();

	glBindTexture(GL_TEXTURE_2D,0);
}

void  Player::shoot() {
	Projectile p;
	_projectiles.push_back(p);
	glm::vec2 WorldCursorPosition = GameManager::camera->screentoWorld(GameManager::mousePosition.x, GameManager::mousePosition.y);
	float angle = std::atan2(WorldCursorPosition.y - _playerSprite.y, WorldCursorPosition.x - _playerSprite.x) * 180 / (float)M_PI;
	_projectiles.back().init(_playerSprite.x,_playerSprite.y + 32, 64, angle, 512, "Game/Textures/proj.png");
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
