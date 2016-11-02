#pragma once
#include <Engine/Camera2D.h>
#include <vector>
#include <Engine/Vertex.h>
#include <Engine/Font.h>

namespace Anchor {
	enum AnchorPoint {
		CENTRE,
		RIGHT, TOP, LEFT, BOTTOM,
		TOP_RIGHT, TOP_LEFT, BOTTOM_LEFT, BOTTOM_RIGHT
	};
}

class NormalisedColour {
public:
	float r, g, b, a;

	NormalisedColour() : r(1), g(1), b(1), a(1) {};
	NormalisedColour(float r, float g, float b) : r(r), g(g), b(b) {};
	NormalisedColour(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {};

	glm::vec4 vec4() { return glm::vec4(r, g, b, a); };
};

class Button {
public:
	Anchor::AnchorPoint anchor;
	float x, y, width, height;
	const char* label;
	NormalisedColour colour, hoverColour, textColour;

	bool active;

	Button() {};
	Button(float x, float y, float w, float h) : x(x),y(y),width(w),height(h) {};
};

class GUI
{
private:
	static std::vector<Button> _buttons;
	static Camera2D* _camera;
public:
	GUI();
	~GUI();

	static void setCam(Camera2D& c) { _camera = &c; };
	static bool getActiveButton(float,float,Button&);
	static Button* addButton(Button);
	static void render(Camera2D&);
	static void renderText(Font&,Shader&);
};

