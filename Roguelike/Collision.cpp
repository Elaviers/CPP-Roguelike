#include "Collision.h"
#include <GL/glew.h>
#include "Game.h"

Collision::Collision()
{
}


Collision::~Collision()
{
}


void rectangle(int x,int y,int x2, int y2, float r, float g, float b) { //Not a class member for some reason
	/*
	SDL_Renderer *gRenderer = NULL;	
	SDL_Rect fillRect = { WIDTH / 4, HEIGHT / 4, WIDTH / 2, HEIGHT / 2 };
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect);
	*/
	float xf = (float)x / WIDTH * 2 -1;
	float yf = (float)y / HEIGHT * 2 - 1;
	float x2f = (float)x2 / WIDTH * 2 - 1;
	float y2f = (float)y2 / HEIGHT * 2 - 1;

	glColor3d(r,g,b);
	glRectd(xf,yf,x2f,y2f);
}
