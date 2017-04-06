#include "Player.h"

#include "Game.h"
#include "GameData.h"
#include "GameManager.h"
#include "Projectile.h"

#include <Engine/GUI.H>
#include <Engine/LineRenderer.h>
#include <Engine/ResourceManager.h>

bool u, d, l, r;

void Player::init(int x,int y,int size,int crosshairSize,std::string texture, std::string texture1) {
	_crosshair.init(0, 0, (float)crosshairSize, (float)crosshairSize, false, texture);
	_crosshair.setOrigin(0,0);
	_playerSprite.UVGridDivisions = 3;
	_playerSprite.init((float)x, (float)y, (float)size, (float)size, false, texture1);
	_playerSprite.setOrigin(0, -1.f);
	ResourceManager::getTexture("Game/Textures/proj.png");//Cache projectile texture

	position = Vector2f{ (float)x, (float)y };
	collision = Rect{ Vector2f{-32,0}, Vector2f{32,64} };
}

void Player::update() {
	if (_shooting && GameData::runTime - _lastShot > fireRate) {
		_lastShot = GameData::runTime;
		shoot();
	}
}

void Player::render(Shader& shader,float frameTime) {
	float movex = _moveX * moveSpeed * frameTime;
	float movey = _moveY * moveSpeed * frameTime;

	shader.set2f("UVOffset", 0, 0); 
	shader.setMat4("transform",glm::mat4());

	if (movex != 0) {
		Tile* collide = GameData::level->rectOverlaps(position + collision.min + Vector2f{ movex, 0 }, position + collision.max + Vector2f{ movex, 0 }, 0);
		if (collide)
			movex = (movex >= 0 ? collide->position.x - (position.x + collision.max.x) : (collide->position.x + 64) - (position.x + collision.min.x));
	}

	if (movey != 0) {
		Tile* collide = GameData::level->rectOverlaps(position + collision.min + Vector2f{ 0, movey }, position + collision.max + Vector2f{ 0, movey }, 0);
		if (collide)
			movey = (movey >= 0 ? collide->position.y - (position.y + collision.max.y) : (collide->position.y + 64) - (position.y + collision.min.y));
	}

	position.x += movex;
	position.y += movey;

	_playerSprite.setPosition(position.x,position.y);
	GameData::camera->setPosition(position);

	//std::cout << "X:" << _playerSprite.x << " Y:" << _playerSprite.y << std::endl;

	_playerSprite.render();

	Vector2f WorldCursorPosition = GameData::camera->screentoWorld(GameData::mousePosition.x, GameData::mousePosition.y);
	_crosshair.setPosition(WorldCursorPosition.x, WorldCursorPosition.y);
	_crosshair.render();

	glBindTexture(GL_TEXTURE_2D,0);

	/*LineRenderer::clear();
	LineRenderer::addLine(position.x + collision.min.x, position.y + collision.min.y, position.x + collision.max.x, position.y + collision.min.y);
	LineRenderer::addLine(position.x + collision.min.x, position.y + collision.min.y, position.x + collision.min.x, position.y + collision.max.y);
	LineRenderer::addLine(position.x + collision.max.x, position.y + collision.min.y, position.x + collision.max.x, position.y + collision.max.y);
	LineRenderer::addLine(position.x + collision.min.x, position.y + collision.max.y, position.x + collision.max.x, position.y + collision.max.y);*/
}

void  Player::shoot() {
	Vector2f WorldCursorPosition = GameData::camera->screentoWorld(GameData::mousePosition.x, GameData::mousePosition.y);
	float angle = std::atan2(WorldCursorPosition.y - (_playerSprite.y + 64), WorldCursorPosition.x - _playerSprite.x) * 180 / (float)M_PI;

	Projectile* p = new Projectile();
	p->init(_playerSprite.x,_playerSprite.y + 64, 64, angle, 512, "Game/Textures/proj.png");
	GameManager::addEntity(p);
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
