#include "Player.h"
#include "Game.h"
#include <math.h>

int s;
GLuint textureIDc,textureID;

void Player::init(int x,int y,int size,std::string texture) {
	_crosshair.init(x, y, size, size, false, texture);
	_sprite.init(WIDTH / 2-64, HEIGHT / 2-64, 128, 128, false, "pointer.png");
	textureIDc = _crosshair.getTextureID();
	textureID = _sprite.getTextureID();
	s = size;
}

void Player::updateMousePosition() {
	SDL_GetMouseState(&mouseX, &mouseY);
	mouseY = HEIGHT-mouseY;
}

void Player::render(GLSLShading shader,Camera2D& cam) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureIDc);

	_crosshair.setPosition(mouseX-(s/2), mouseY-(s/2));
	_crosshair.render(shader,cam.getCameraMatrix());

	glBindTexture(GL_TEXTURE_2D, textureID);
	_sprite.rotation = std::atan2(mouseY-HEIGHT/2,mouseX-WIDTH/2) * 180/M_PI;
	_sprite.render();

	glBindTexture(GL_TEXTURE_2D, 0);
}
