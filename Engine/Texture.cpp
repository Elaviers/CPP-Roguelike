#include "Texture.h"

void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D,ID);
}