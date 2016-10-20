#include "Player.h"
#include <iostream>

Player::Player()
{
}


Player::~Player()
{
}

bool north, east, south, west;
float walkspeed = 256;
GLuint tID;

void Player::init(float x,float y) {
	_playerSprite.UVGridDivisions = 8;
	_playerSprite.rotation = 0;
	_playerSprite.init(x,y,256,256,false, "resource/textures/sprites.png");
	_playerSprite.dbg = true;
	tID = _playerSprite.getTextureID();
}

void Player::render(Shader shader,Camera2D &camera,float deltaTime) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,tID);

	float moveAmount = walkspeed * deltaTime;
	_playerSprite.setPosition(_playerSprite.x + (east  ? moveAmount : 0) + (west  ? -moveAmount : 0),
							  _playerSprite.y + (north ? moveAmount : 0) + (south ? -moveAmount : 0));

	_playerSprite.render(shader,camera.getCameraMatrix());

	glBindTexture(GL_TEXTURE_2D, 0);
}

int uvlocation;

void Player::handleDirection(bool n,bool e,bool s,bool w,bool value) {
	if (n)north = value;
	if (e)east = value;
	if (s)south = value;
	if (w)west = value;

	_playerDirection = north&&east ? 1 : east&&south ? 3 : south&&west ? 5 : west&&north ? 7 : 
						north ? 0 : east ? 2 : south ? 4 : west ? 6 : _playerDirection;

	if (_playerDirection > 4)
		uvlocation = -(4 - (_playerDirection - 4));
	else uvlocation = _playerDirection;

	_playerSprite.swapUVs(uvlocation);
}

void Player::keyDown(SDL_Keycode scancode) {
	if (scancode == SDLK_UP || scancode == SDLK_RIGHT || scancode == SDLK_DOWN || scancode == SDLK_LEFT)
		handleDirection(scancode == SDLK_UP,
			scancode == SDLK_RIGHT,
			scancode == SDLK_DOWN,
			scancode == SDLK_LEFT,true);
}

void Player::keyUp(SDL_Keycode scancode) {
	if (scancode == SDLK_UP || scancode == SDLK_RIGHT || scancode == SDLK_DOWN || scancode == SDLK_LEFT)
		handleDirection(scancode == SDLK_UP,
			scancode == SDLK_RIGHT,
			scancode == SDLK_DOWN,
			scancode == SDLK_LEFT, false);
}