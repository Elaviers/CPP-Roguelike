#pragma once
#include <GL/glew.h>
#include "Texture.h"
#include "Shader.h"
#include <glm/glm.hpp>

class SpriteRenderer
{
private:
	static GLuint _vbo, _vao;
	static int _currentIndex,_divisions;
	static glm::vec2 _UVOffset;

	static Shader _shader;

	static void setIndex(int i);
	static void setUVData(int);
public:
		
	static void init();
	static void SetShaderActive(bool);
	static void drawSprite(Texture& Texture, float x, float y, float width, float height, float angle = 0.0f, int Divisions = 1, int Index = 0);
	static void drawSprite(Shader& Shader, Texture& Texture, float x, float y, float width, float height, float angle = 0.0f,int Divisions = 1, int Index = 0);
};