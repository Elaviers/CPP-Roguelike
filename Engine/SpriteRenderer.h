#pragma once
#include <GL/glew.h>
#include "Texture.h"
#include "Shader.h"

class SpriteRenderer
{
private:
	GLuint _vbo, _vao;
public:
	SpriteRenderer();
	~SpriteRenderer();
		
	void init();
	void drawSprite(Shader Shader,Texture& Texture,float x,float y,float width,float height,float angle);
};
