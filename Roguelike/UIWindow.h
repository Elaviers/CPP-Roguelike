#pragma once
#include "Types.h"

#include <Engine/UIButton.h>
#include <vector>

class UIWindow : public UIContainer {
	UIContainer	titleBar;
	UIRect		titleRect;
	UIText		titleText;
	UIButton	closeButton;
	UIRect		bg;

public:
	UIWindow(float x, float y, float w, float h, uByte flags, const char* name, const char* font, bool addCloseButton = true);
	virtual ~UIWindow();

	void bind_close(void(*function)()) { closeButton.bind_onClick(function); }
	void bind_close(void(*function)(UIElement*)) { closeButton.bind_onClick(function); };

	static void CloseWindow(UIElement* closeButton);
};

class Window_LevelSelect : public UIWindow {
	std::vector<UIButton*> _buttons;

public:
	static bool status;

	Window_LevelSelect(float x, float y, float w, float h, unsigned char flags);
	~Window_LevelSelect() { status = false; };

	void(*levelonclick)(UIElement*);
	void bind_level(void(*function)(UIElement*));

	void refresh();
};
