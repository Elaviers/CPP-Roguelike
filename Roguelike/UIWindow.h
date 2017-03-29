#pragma once
#include <Engine/GUI.h>

class UIWindow : public GUI::UIContainer
{
public:
	UIWindow(float x,float y,float w,float h,unsigned char flags, const char* name, const std::string&);
	~UIWindow();

	void bind_close(void(*function)()) { closeButton->bind_onClick(function); }
	void bind_close(void(*function)(UIElement*)) { closeButton->bind_onClick(function); };
private:
	GUI::UIContainer *titleBar;
	GUI::UIRect *titleRect;
	GUI::UIText *titleText;
	GUI::Button *closeButton;
	GUI::UIRect *bg;
};

