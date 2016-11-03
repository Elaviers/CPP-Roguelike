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

	enum Lock {
		NORMALISED_X = 0x01,
		NORMALISED_Y = 0x02,
		NORMALISED_WIDTH = 0x04,
		NORMALISED_HEIGHT = 0x08
	};

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
	float x, y, width, height;
	int offset_x, offset_y;
	const char* label;
	NormalisedColour colour, hoverColour, textColour;
	unsigned char normalised;

	bool active;

	Button() {};
	Button(float x, float y, float w, float h,unsigned char normalisedCoords) : x(x),y(y),width(w),height(h),normalised(normalisedCoords) {};

	void (*onClick)();
	void render(Camera2D&);
	void setAnchor(Anchor::AnchorPoint);
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
	static bool update(float,float);
	static Button* addButton(Button&);
	static void render();
	static void renderText(Font&,Shader&);

	static void click();
};

