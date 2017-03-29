#pragma once
#include "UIPrimitives.h"

class GlobalUI {
private:
	static GUI::UIContainer _root;
	static std::vector<GUI::UIElement*> _elementsToDelete;
public:
	static bool update(int mouseX, int mouseY);
	static void add(GUI::UIElement&);
	static void add(GUI::UIElement*);
	static void remove(GUI::UIElement*);
	static void deleteElement(GUI::UIElement*); //marks this element and all children to be deleted next time update is called
	static void setCameraSize(int, int);
	static void render(Shader*);
	static void click();
};

namespace GUI {
	extern Vector2f cameraScale;
	typedef void(*buttonEvent)(UIElement* caller);

	class Button : public UIContainer {
	private:
		bool _active;
		NormalisedColour _colour, _hoverColour;

		void (*_event_onClick)(UIElement *caller);
		void(*_event_onClick_basic)();
	public:
		Button(float x, float y, float width, float height, unsigned char flags);
		virtual ~Button() { _elements.clear(); }; //Destructor clears children so that the UIContainer will not try to delete their pointers

		void setColour(const NormalisedColour& c) { _colour = c; panel.setColour(c); };
		void setHoverColour(const NormalisedColour& c) { _hoverColour = c; };

		UIRect panel;
		UIText label;

		bool isOverlapping(const int, const int) override;
		bool click() override;

		void bind_onClick(void(*function)(UIElement *caller)) { _event_onClick = function; };
		void bind_onClick(void(*function)()) { _event_onClick_basic = function; };
	};

	class TextBox : public UIContainer {
	private:
		bool _hover, _active;
		NormalisedColour _colour, _selectColour;
	public:
		TextBox(float x, float y, float width, float height, unsigned char flags);
		virtual ~TextBox() { _elements.clear(); }; //See Button

		void setColour(const NormalisedColour& c) { _colour = c; panel.setColour(c); };
		void setSelectColour(const NormalisedColour& c) { _selectColour = c; };

		UIRect panel;
		UIText label;

		void(*onStateChanged)(bool state);

		bool isOverlapping(const int, const int) override;
		bool click() override;

		void textInput(char newchar);
	};


}
