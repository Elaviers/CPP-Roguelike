#pragma once
#include <GL/glew.h>
#include "Texture.h"
#include "Shader.h"
#include "Vertex.h"
#include <glm/glm.hpp>
#include "Camera2D.h"

class SpriteRenderer
{
private:
	static GLuint _vbo, _vao;
	static int _currentIndex,_divisions;
	static Colour _lastColour;
	static glm::vec2 _UVOffset;

	static Shader _shader;

	static void setIndex(int i);
	static void setUVData(int,Colour);
public:
		
	static void init();
	static void UseProgram(const Camera2D&);
	static void UnuseProgram();

	static void drawSprite(const Texture& Texture, Vector2f Corner1, Vector2f Corner2, float x, float y, float width, float height, float angle = 0.0f, int Divisions = 1, int Index = 0);
	static void drawSprite(const Texture& Texture, Vector2f Corner1, Vector2f Corner2, float x, float y, float width, float height, Colour colour, float angle = 0.0f, int Divisions = 1, int Index = 0);

	static void drawSprite(const Texture& Texture, float x, float y, float width, float height, float angle = 0.0f, int Divisions = 1, int Index = 0);
	static void drawSprite(const Texture& Texture, float x, float y, float width, float height, Colour colour, float angle = 0.0f, int Divisions = 1, int Index = 0);

	static void drawSprite(Shader& Shader, const Texture& Texture, float x, float y, float width, float height, float angle = 0.0f,int Divisions = 1, int Index = 0);
	static void drawSprite(Shader& Shader, const Texture& Texture, float x, float y, float width, float height, Colour colour, float angle = 0.0f, int Divisions = 1, int Index = 0);
};
