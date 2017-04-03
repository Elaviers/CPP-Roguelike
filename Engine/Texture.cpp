#include "Texture.h"

void Texture::bind() const {
	glBindTexture(GL_TEXTURE_2D,ID);
}