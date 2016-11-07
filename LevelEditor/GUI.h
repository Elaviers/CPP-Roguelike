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

class UIElement {
public:
	float x, y, width, height;
	int offset_x, offset_y;
	unsigned char normalised;

	virtual bool update(float, float, Camera2D&) = 0;
	virtual void render(Camera2D&) = 0;
	virtual void renderLabel(Font&,Shader&,Camera2D&) = 0;

	void setAnchor(Anchor::AnchorPoint);

	UIElement(float x, float y, float w, float h,unsigned char flags) : x(x), y(y), width(w), height(h), normalised(flags) {};
};

class Button : public UIElement {
public:
	const char* label;
	NormalisedColour colour, hoverColour, textColour;

	bool active;
	
	Button() : UIElement(0,0,0,0,0) {};
	Button(float x, float y, float w, float h, unsigned char normalisedCoords) : UIElement(x,y,w,h,normalisedCoords) {};

	void (*onClick)();

	bool update(float x,float y,Camera2D&) override;
	void render(Camera2D&) override;
	void renderLabel(Font&, Shader&, Camera2D&) override;
};

class GUI
{
private:
	static std::vector<UIElement*> _elements;
	static Camera2D* _camera;
public:
	static void setCam(Camera2D& c) { _camera = &c; };
	static bool update(float,float);
	static void addButton(Button&);
	static void render();
	static void renderText(Font&,Shader&);

	static void click();
};

