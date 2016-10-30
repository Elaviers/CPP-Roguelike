#include "GUI.h"
#include <GL/glew.h>


GUI::GUI()
{
}


GUI::~GUI()
{
}

void GUI::addButton(float x, float y, float x2, float y2,const char* s) {
	_buttons.push_back(Button{x,y,x2,y2,s});
}

void GUI::render(Camera2D& cam) {
	int ScreenWidth = cam.getWidth() * 2 - 1;
	int ScreenHeight = cam.getHeight() * 2 - 1;

	//glColor3d(r, g, b);
	//glRectd(x / ScreenWidth, y / ScreenHeight, x2 / ScreenWidth, y2f / ScreenHeight);
}