#pragma once

#include <Gl/glew.h>

struct Vector2 { float x, y; };

struct UV { 
	float u, v;
	void set(float uValue, float vValue) { u = uValue; v = vValue; }
};

class Colour { 
public:
	GLubyte r, g, b, a;
	Colour() : r(255),g(255),b(255),a(255) {};
};

struct Vertex {
	Vector2 position;
	Colour colour;
	UV uv;

	void setPosition(float x, float y) { position.x = x; position.y = y; }
	void setColour(GLubyte r, GLubyte b, GLubyte g, GLubyte a) { colour.r = r; colour.g = g; colour.b = b; colour.a = a; }
	void setUv(float u, float v) { uv.u = u; uv.v = v; }

	static Colour colourOf(GLuint r, GLuint g, GLuint b, GLuint a) 
	{ Colour c; c.r = r; c.g = g, c.b = b, c.a = a; return c; }
};