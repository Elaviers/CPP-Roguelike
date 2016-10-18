#include "Misc.h"
#include <GL/glew.h>

void misc::rectangle(int x,int y,int x2, int y2, float r, float g, float b,int ScreenWidth,int ScreenHeight) { //Not a class member for some reason
	float xf = (float)x / ScreenWidth * 2 -1;
	float yf = (float)y / ScreenHeight * 2 - 1;
	float x2f = (float)x2 / ScreenWidth * 2 - 1;
	float y2f = (float)y2 / ScreenHeight * 2 - 1;

	glColor3d(r,g,b);
	glRectd(xf,yf,x2f,y2f);
}
