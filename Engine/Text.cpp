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
	for (int i = 0; i < _len; i++)
		indices[i] = str[i] - 32;

	Sprite *l = new Sprite[_len];
	for (int i = 0; i < _len; i++) {
		if (indices[i] > -1) {
			Sprite character;
			character.init(x,y,size,size,false,texture);
			character.swapUVs(indices[i]);
			character.setPosition(i*size, 64);
		}
	}
}

void Text::init(int pos_x, int pos_y, char tex[],int fontSize) {
	size = fontSize;
	x = pos_x;
	y = pos_y;
	texture = tex;

	font.UVGridDivisions = 16;
	font.init(x, y, size, size, false, texture);
}

void Text::render(GLSLShading shader, glm::mat4 cMat) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, font.getTextureID());
	for (int i = 0; i < _len; i++) {
		if (indices[i] > -1) {
			font.swapUVs(indices[i]);
			font.setPosition(i*size,64);
			font.render(shader, cMat);
		}
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}