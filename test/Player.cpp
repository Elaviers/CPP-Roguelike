#include "Player.h"
#include <GLM/glm.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

GLuint ID;

void Player::init(float x, float y,float w,float h) {
	_sprite.UVGridDivisions = 1;
	_sprite.rotation = 0;
	_sprite.init(x,y,w,y,true,"stuff/player.png");
	ID = _sprite.getTextureID();
}

void Player::updateCursorLocation(float x,float y) {
	_sprite.rotation = glm::atan(_sprite.y,_sprite.x) * 180 / M_PI;
}

void Player::render(GLSLShading shader,Camera2D cam,float deltaTime) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ID);
	_sprite.render(shader,cam.getCameraMatrix());
	glBindTexture(GL_TEXTURE_2D, 0);
}