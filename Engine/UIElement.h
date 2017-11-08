#pragma once
#include "Vector2.h"

class Shader;

namespace GUI {
	extern Vector2f cameraScale;

	enum UIFlags {
		NORMALISED_X = 0x01,
		NORMALISED_Y = 0x02,
		NORMALISED_WIDTH = 0x04,
		NORMALISED_HEIGHT = 0x08,
		FLIPPED_X = 0x10,
		FLIPPED_Y = 0x20
	};
}

class UIElement //Base UI element which ultimately attempts to store two Vector2s representing the normalised coordinates of the bounding box.
	{
	protected:
		UIElement* _parent;
		Vector2f _position, _size;
		Vector2f _min, _max; //These are the normalised coordinates of each corner
		unsigned char _flags;
		//construction
		UIElement(float x, float y, float w, float h, unsigned char flags);
		UIElement() : UIElement(0, 0, 1, 1, GUI::NORMALISED_WIDTH | GUI::NORMALISED_HEIGHT) {};
	public:
		virtual ~UIElement();
		//Basic setters
		void setFlags(unsigned char flags) { _flags = flags; };
		void addFlags(unsigned char flags) { _flags |= flags; };
		void setParent(UIElement& element, const bool recalc = true) { setParent(&element, recalc); };
		void setParent(UIElement* elementp, const bool recalc = true) { _parent = elementp; if (recalc)calculate(); };
		UIElement* getParent() { return _parent; };
		//Defined setters
		void setX(float x) { _position.x = x; calculate(); }; //Just sets the x of corner 1. Normalises x if necessary.
		void setY(float y) { _position.y = y; calculate(); }; //Just sets the y of corner 1. Normalises y if necessary.
		void setWidth(float width) { _size.x = width; calculate(); }; //Sets the x of corner 2 to corner 1's x plus a normalised version of width
		void setHeight(float height) { _size.y = height; calculate(); }; //Sets the y of corner 2 to corner 1's y plus a normalised version of height
		//Basic getters. All values are normalised.
		float getX() const { return _min.x; };
		float getY() const { return _min.y; };
		float getWidth() const { return _max.x - _min.x; };
		float getHeight() const { return _max.y - _min.y; };
		//virtual functions
		virtual void render(Shader *shader) {};
		virtual bool click() { return false; }; //returns whether or not to 'consume' input
		virtual bool isOverlapping(const int px, const int py); //Checks if specified point overlaps with the element's bounds
		virtual void calculate(); //recalculates the normalised coordinates for any not-normalised variables.
};
