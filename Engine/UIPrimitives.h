#pragma once
#include "Vertex.h"//For Vector2f
#include "Font.h"
#include "Shader.h"

#include <vector>

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

	class UIElement //Base UI element which ultimately attempts to store two Vector2s representing the normalised coordinates of the bounding box.
	{
	protected:
		UIElement* _parent;
		Vector2f _position, _size;
		Vector2f _min, _max; //These are the normalised coordinates of each corner
		unsigned char _flags;
		//construction
		UIElement(float x, float y, float w, float h, unsigned char flags);
		UIElement() : UIElement(0, 0, 1, 1, NORMALISED_WIDTH | NORMALISED_HEIGHT) {};
	public:
		virtual ~UIElement() {};
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

	class UIContainer : public UIElement
	{
	protected:
		std::vector<UIElement*> _elements;
	public:
		UIContainer(float x, float y, float w, float h, unsigned char f) : UIElement(x, y, w, h, f) {};
		virtual ~UIContainer();

		void addElement(UIElement& element, const bool recalc = true) { _elements.push_back(&element); element.setParent(this, recalc); };
		void addElement(UIElement* elementp, const bool recalc = true) { _elements.push_back(elementp); elementp->setParent(this, recalc); };
		std::vector<UIElement*>* getChildren() { return &_elements; };
		void removeElement(UIElement* element);

		void render(Shader *shader) override;
		bool click() override;
		bool isOverlapping(const int x, const int y) override;//returns true if any of the children of this root overlap with the point given
		void calculate() override;
	};

	class UIRect : public UIElement
	{
	private:
		NormalisedColour _colour;
	public:
		void setColour(const NormalisedColour &colour) { _colour = colour; };

		void render(Shader*) override;

		UIRect(float x, float y, float w, float h, unsigned char f) : UIElement(x, y, w, h, f) {};
		UIRect() {};
		virtual ~UIRect() { std::printf("Destroy UIRECT (%p)\n",this); };
	};

	class UIText : public UIElement
	{
	private:
		NormalisedColour _colour;
		Font* _font;
	public:
		std::string text;
		void setColour(const NormalisedColour &colour) { _colour = colour; };
		void setFont(const std::string& font);

		void render(Shader*) override;

		const std::string& operator=(const std::string& rhs) { text = rhs; return text; };

		UIText(float x, float y, float w, float h, unsigned char f) : UIElement(x, y, w, h, f) {};
		UIText() {};
		virtual ~UIText() { std::printf("Destroy UITEXT (%p)\n",this); };
	};

}
