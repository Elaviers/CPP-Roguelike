#pragma once
#include "Colour.h"
#include "Vector2f.h"

struct UV { 
	float u, v;
	void set(float uValue, float vValue) { u = uValue; v = vValue; }
};

struct Vertex {
	Vector2f position;
	Colour colour;
	UV uv;

	void setPosition(float x, float y) { position.x = x; position.y = y; }
	void setColour(GLubyte r, GLubyte b, GLubyte g, GLubyte a) { colour.r = r; colour.g = g; colour.b = b; colour.a = a; }
	void setUv(float u, float v) { uv.u = u; uv.v = v; }

	static Colour colourOf(int r, int g, int b, int a)
	{
		return Colour{ (GLubyte)r, (GLubyte)g, (GLubyte)b, (GLubyte)a };
	}
};
