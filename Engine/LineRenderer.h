#pragma once
#include <vector>
#include "Shader.h"
#include "Vertex.h"
#include "Camera2D.h"

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
	static void drawLine(float x,float y,float x2,float y2,Colour colour); //Adds a line to be rendered
	static void drawLine(float x,float y,float x2,float y2) { drawLine(x,y,x2,y2,Colour()); }; //Adds a white line to be rendered
	static void render(Camera2D&); //Renders lines
};

