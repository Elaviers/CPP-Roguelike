#pragma once
#include "Camera2D.h"
#include "Vertex.h"
#include "Font.h"
#include <vector>

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

	void set(float red, float green, float blue) { r = red; g = green; b = blue; };
	void set(float red, float green, float blue, float alpha) { r = red; g = green; b = blue; a = alpha; };

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

	virtual void render(Camera2D&) = 0;
	virtual void click() {};
	virtual bool update(float, float, Camera2D&) { return false; };
	virtual void renderLabel(Font&, Shader&, Camera2D&) {};

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
	void click() { if(active)onClick(); };
};

class TextBox : public UIElement {
public:
	std::string text;
	NormalisedColour colour,colour2,textColour;

	bool hover,active;

	void (*onStateChanged)(bool state);

	TextBox() : UIElement(0,0,0,0,0) {};
	TextBox(float x, float y, float w, float h, unsigned char flags) : UIElement(x, y, w, h, flags), active(false) {};

	bool update(float x, float y, Camera2D&) override;
	void render(Camera2D&) override;
	void renderLabel(Font&, Shader&, Camera2D&) override;
	void click() override;

	void textInput(char newchar);
};

class GUI
{
private:
	static std::vector<UIElement*> _elements;
	static Camera2D* _camera;
public:
	static void setCam(Camera2D& c) { _camera = &c; };
	static bool update(float,float);
	static void add(UIElement&);
	static void render();
	static void renderText(Font&,Shader&);

	static void click();
};

