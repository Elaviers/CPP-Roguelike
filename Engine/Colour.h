#pragma once
#include <GL/glew.h>

enum Colours { BLACK, WHITE, RED, GREEN, BLUE };

class Colour
{
public:
	Colour();
	~Colour();

	GLubyte r, g, b, a;
};

