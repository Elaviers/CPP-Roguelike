#include "Player.h"
#include <GLM/glm.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

GLuint ID;

void Player::init(float x, float y,float w,float h) {
	_crosshair.UVGridDivisions = 1;
	_crosshair.rotation = 0;
	_crosshair.init(x,y,w,y,true,"stuff/player.png");
	ID = _crosshair.getTextureID();
}

void Player::updateCursorLocation(float x,float y) {
	_crosshair.rotation = glm::atan(_crosshair.y,_crosshair.x) * 180 / M_PI;
}

void Player::render(GLSLShading shader,Camera2D cam,float deltaTime) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ID);
	_crosshair.render(shader,cam.getCameraMatrix());
	glBindTexture(GL_TEXTURE_2D, 0);
}