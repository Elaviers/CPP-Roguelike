#pragma once
#include "Sprite.h"
#include "Vertex.h"
#include <string>
#include <vector>
class Text
{
public:
	Text();
	~Text();
	float x, y;
	char *texture;
	void operator=(std::string str);
	void init(int x,int y,char texture[], int fontSize = 16);
	void render(GLSLShading shader, glm::mat4 cMat);
	void setText(std::string text);
	Colour colour;
	Sprite font;
	int size;
private:
	std::string _text;
	unsigned int _len;
	char *indices;
};

