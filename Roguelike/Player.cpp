#include "Player.h"
#include "Game.h"

int s;
GLuint textureID;

void Player::init(int x,int y,int size,std::string texture) {
	_sprite.init(x, y, size, size, false, texture);
	textureID = _sprite.getTextureID();
	s = size;
}

void Player::updateMousePosition() {
	SDL_GetMouseState(&mouseX, &mouseY);
}

void Player::render(GLSLShading shader,Camera2D& cam) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	_sprite.setPosition(mouseX-(s/2), HEIGHT-mouseY-(s/2));
	_sprite.render(shader,cam.getCameraMatrix());

	glBindTexture(GL_TEXTURE_2D, 0);
}
