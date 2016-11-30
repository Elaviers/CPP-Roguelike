#pragma once
#include "UIPrimitives.h"

namespace GUI {

	class Button : public UIElement {
	private:
		bool _active;
	public:
		NormalisedColour colour, hoverColour;

		UIRect panel;
		UIText label;

		void(*onClick)();

		void render(Font&, Shader&) override;
		bool isOverlapping(int, int) override;
		void click() override { if (_active)onClick(); };

		Button(float x, float y, float w, float h, unsigned char flags) :
			UIElement(x,y,w,h,flags)
		{
			panel.setParent(*this);
			label.setParent(*this);
		};
	};

	class TextBox : public UIElement {
	private:
		bool _hover, _active;
	public:
		UIRect panel;
		UIText label;

		TextBox(float x, float y, float w, float h, unsigned char flags) :
			UIElement(x, y, w, h, flags)
		{
			panel.setParent(*this);
			label.setParent(*this);
		};

		void(*onStateChanged)(bool state);

		void render(Font&, Shader&) override;
		void click() override;

		void textInput(char newchar);
	};

	class Handler
	{
	private:
		static std::vector<UIElement*> _elements;
		static Camera2D* _camera;
	public:
		static void setCam(Camera2D& c) { _camera = &c; UIElement::setCameraSize(c.getWidth(), c.getHeight()); };
		static bool update(int, int);
		static void add(UIElement&);
		static void render(Font&, Shader&);

		static void click();
	};

}