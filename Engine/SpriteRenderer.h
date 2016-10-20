#pragma once
#include <GL/glew.h>
#include "Texture.h"
#include "Shader.h"
#include <glm/glm.hpp>

class SpriteRenderer
{
private:
	GLuint _vbo, _vao;
	int _currentIndex,_divisions;
	glm::vec2 _UVOffset;

	void setIndex(int i);
public:
	SpriteRenderer();
	~SpriteRenderer();
		
	void init(int divisions);
	void drawSprite(Shader Shader,Texture& Texture,float x,float y,float width,float height,float angle = 0.0f,int Index = 0);
};
