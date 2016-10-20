#include "Text.h"


Text::Text() {
}


Text::~Text() {
}

void Text::operator=(std::string rhs) {
	setText(rhs);
}

void Text::setText(std::string str) {
	_len = str.length();
	indices = new char[_len]; 
	for (unsigned int i = 0; i < _len; i++)
		indices[i] = str[i] - 32;

	Sprite *l = new Sprite[_len];
	for (unsigned int i = 0; i < _len; i++) {
		if (indices[i] > -1) {
			Sprite character;
			character.init(x,y,(float)size,(float)size,false,texture);
			character.swapUVs(indices[i]);
			character.setPosition((float)i*size, 64);
		}
	}
}

void Text::init(int pos_x, int pos_y, char tex[],int fontSize) {
	size = fontSize;
	x = (float)pos_x;
	y = (float)pos_y;
	texture = tex;

	font.UVGridDivisions = 16;
	font.init(x, y, (float)size, (float)size, false, texture);
}

void Text::render() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, font.getTextureID());
	for (unsigned int i = 0; i < _len; i++) {
		if (indices[i] > -1) {
			font.swapUVs(indices[i]);
			font.setPosition((float)i*size,64);
			font.render();
		}
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}