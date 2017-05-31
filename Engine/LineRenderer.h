#pragma once
#include "Camera2D.h"
#include "Colour.h"
#include "Shader.h"
#include "Vector2.h"

#include <glm/vec2.hpp>
#include <vector>

class LineRenderer
{
private:
	struct VertexNoUV {
		glm::vec2 Position;
		Colour Colour;
	};

	static std::vector<VertexNoUV> _vertices;
	static GLuint _vbo, _vao;
	static Shader _shader;
public:
	static void init(); //Creates shader and VAO/VBO
	static void addLine(float x, float y, float x2, float y2, Colour colour); //Adds a line to be rendered
	static void addLine(float x, float y, float x2, float y2) { addLine(x, y, x2, y2, Colour()); }; //Adds a white line to be rendered
	static void clear();
	static void render(const Camera2D&); //Renders lines
};
