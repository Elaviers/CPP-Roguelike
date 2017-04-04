#pragma once
#include <Engine/Button.h>
#include <vector>

class UIWindow : public GUI::UIContainer
{
public:
	UIWindow(float x,float y,float w,float h,unsigned char flags, const char* name, const std::string&,bool addCloseButton = true);
	virtual ~UIWindow();

	void bind_close(void(*function)()) { closeButton.bind_onClick(function); }
	void bind_close(void(*function)(UIElement*)) { closeButton.bind_onClick(function); };

	static void CloseWindow(UIElement* closeButton);
private:
	GUI::UIContainer titleBar;
	GUI::UIRect titleRect;
	GUI::UIText titleText;
	GUI::Button closeButton;
	GUI::UIRect bg;
};

class Window_LevelSelect : public UIWindow {
protected:
	std::vector<GUI::Button*> _buttons;

public:
	static bool status;

	Window_LevelSelect(float x,float y,float w,float h,unsigned char flags);
	~Window_LevelSelect() { status = false; };

	void(*levelonclick)(UIElement*);
	void bind_level(void (*function)(UIElement*));

	void refresh();
};
