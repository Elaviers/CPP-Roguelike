#pragma once

typedef unsigned char GLubyte;

class Colour {
public:
	GLubyte r, g, b, a;
	Colour() : r(255), g(255), b(255), a(255) { r, g, b, a; };
	Colour(GLubyte c) : r(c), g(c), b(c) {};
	Colour(GLubyte r, GLubyte g, GLubyte b) : r(r), g(g), b(b), a(255) {};
	Colour(GLubyte r, GLubyte g, GLubyte b, GLubyte a) : r(r), g(g), b(b), a(a) {};

	bool operator!=(const Colour& b);
};
