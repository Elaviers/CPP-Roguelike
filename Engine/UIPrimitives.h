#pragma once
#include "Vertex.h"//For Vector2D
#include "Font.h"
#include "Shader.h"
#include "Camera2D.h"

#include <vector>

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

namespace GUI {

	enum UIFlags {
		NORMALISED_X = 0x01,
		NORMALISED_Y = 0x02,
		NORMALISED_WIDTH = 0x04,
		NORMALISED_HEIGHT = 0x08,
		ONEMINUS_X = 0x10,
		ONEMINUS_Y = 0x20
	};

	class UIElement //Base UI element
	{
	protected:
		static Vector2 _cameraSize;

		Vector2 _corner1, _corner2; //These are the normalised coordinates of each corner
		unsigned char _flags;
		UIElement* _parent;
		//construction
		UIElement(float x, float y, float w, float h, unsigned char flags);
		UIElement() : UIElement(0,0,1,1,NORMALISED_WIDTH | NORMALISED_HEIGHT) {};
		virtual ~UIElement() {};
	public:
		//Basic setters
		static void setCameraSize(int w, int h) { _cameraSize.x = (float)w; _cameraSize.y = (float)h; };
		void setFlags(unsigned char flags) { _flags = flags; };
		void setParent(UIElement& element) { _parent = &element; };
		//Defined setters
		void setX(float x); //Just sets the x of corner 1. Normalises x if necessary.
		void setY(float y); //Just sets the y of corner 1. Normalises y if necessary.
		void setWidth(float width); //Sets the x of corner 2 to corner 1's x plus a normalised version of width
		void setHeight(float height); //Sets the y of corner 2 to corner 1's y plus a normalised version of height
		//Basic getters
		float getX() { return _corner1.x; };
		float getY() { return _corner1.y; };
		float getWidth() { return _corner2.x - _corner1.x; };
		float getHeight() { return _corner2.y - _corner1.y; };
		//other
		void recalculate(int newWidth, int newHeight); //recalculates the normalised coordinates for any not-normalised variables.
		//virtual functions
		virtual void render(Font &font, Shader &fontShader) {};
		virtual void click() {};
		virtual bool isOverlapping(int px, int py); //Checks if specified point overlaps with the element's bounds
	};

	class UIRoot : public UIElement
	{
	private:
		std::vector<UIElement*> _elements;
	public:
		void addElement(UIElement& element) { _elements.push_back(&element); element.setParent(element); };

		void render(Font &font, Shader &fontShader) override;
		void click() override;
		bool isOverlapping(int x, int y) override;//returns true if any of the children of this root overlap with the point given

		UIRoot(float x, float y, float w, float h, unsigned char f) : UIElement(x, y, w, h, f) {};
	};

	class UIRect : public UIElement
	{
	private:
		NormalisedColour _colour;
	public:
		void setColour(NormalisedColour colour) { _colour = colour; };

		void render(Font&, Shader&) override;

		UIRect(float x, float y, float w, float h, unsigned char f) : UIElement(x, y, w, h, f) {};
		UIRect() {};
	};

	class UIText : public UIElement
	{
	private:
		NormalisedColour _colour;
		
	public:
		std::string text;
		void setColour(NormalisedColour colour) { _colour = colour; };

		void render(Font&, Shader&) override;

		const std::string& operator=(const char* rhs) { text = rhs; return text; };

		UIText(float x, float y, float w, float h, unsigned char f) : UIElement(x, y, w, h, f) {};
		UIText() {};
	};

}