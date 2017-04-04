#pragma once
#include <glm/vec4.hpp>

class NormalisedColour {
public:
	float r, g, b, a;

	void set(float red, float green, float blue) { r = red; g = green; b = blue; };
	void set(float red, float green, float blue, float alpha) { r = red; g = green; b = blue; a = alpha; };

	NormalisedColour() : r(1), g(1), b(1), a(1) {};
	NormalisedColour(float r, float g, float b) : r(r), g(g), b(b), a(1) {};
	NormalisedColour(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {};

	glm::vec4 vec4() { return glm::vec4(r, g, b, a); };
};
