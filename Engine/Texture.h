#pragma once

typedef unsigned int GLuint;

class Texture {
public:
	GLuint ID;
	int Width, Height;

	void bind() const;
};
