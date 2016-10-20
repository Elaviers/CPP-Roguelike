#pragma once
#include "PicoPNG.h"
#include <Gl/glew.h>

class Texture {
public:
	GLuint ID;
	int Width, Height;

	void bind();
};