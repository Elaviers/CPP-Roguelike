#pragma once
#include "UIPrimitives.h"

class GlobalUI {
private:
	static GUI::UIContainer _root;
public:
	static bool updateMousePosition(int, int);
	static void add(GUI::UIElement&);
	static void add(GUI::UIElement*);
	static void remove(GUI::UIElement*);
	static void setCameraSize(int,int);
	static void render(Shader*);
	static void click();
};

namespace GUI {
	extern Vector2f cameraScale;

	class Button : public UIContainer {
	private:
		bool _active;
		NormalisedColour _colour, _hoverColour;
	public:
		void setColour(NormalisedColour& c) { _colour = c; panel.setColour(c); };
		void setHoverColour(NormalisedColour& c) { _hoverColour = c; };

		UIRect panel;
		UIText label;

		void(*onClick)();

		bool isOverlapping(int, int) override;
		bool click() override;

		Button(float x,float y,float width,float height,unsigned char flags);
	};

	class TextBox : public UIContainer {
	private:
		bool _hover, _active;
		NormalisedColour _colour, _selectColour;
	public:
		void setColour(NormalisedColour& c) { _colour = c; panel.setColour(c); };
		void setSelectColour(NormalisedColour& c) { _selectColour = c; };

		UIRect panel;
		UIText label;

		void(*onStateChanged)(bool state);

		bool isOverlapping(int, int) override;
		bool click() override;

		void textInput(char newchar);

		TextBox(float x,float y,float width,float height,unsigned char flags);
	};


}