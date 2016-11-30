#pragma once
#include <Gl/glew.h>

class Texture {
public:
	GLuint ID;
	int Width, Height;

	void bind();
};