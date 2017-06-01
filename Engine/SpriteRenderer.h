#pragma once
#include "Shader.h"
#include "Vertex.h"

#include <glm/glm.hpp>

class Camera2D;
class Texture;

class SpriteRenderer
{
private:
	static GLuint _vbo, _vao;
	static int _currentIndex, _divisions;
	static Colour _colour;
	static glm::vec2 _UVOffset;

	static Shader _shader;

	static void setIndex(int i);
public:
	static void init();

	static Shader& GetShader() { return _shader; };
	static void UseProgram(const Camera2D&);
	static void UnuseProgram();

	inline static void drawSprite(const Texture& Texture, float x, float y, float width, float height, float angle = 0.0f, int Index = 0) {
		drawSprite(_shader, Texture, x, y, width, height, angle, Index);
	};

	static void setUVData(unsigned char divisions, const Colour&);
	static void drawSprite(Shader& Shader, const Texture& Texture, float x, float y, float width, float height, float angle = 0.0f, int Index = 0);
};
