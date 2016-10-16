#include "Collision.h"
#include "Game.h"



Collision::Collision()
{
}


Collision::~Collision()
{
}


void rectangle() {

	SDL_Renderer *gRenderer = NULL;	

	//Render rect
	SDL_Rect fillRect = { WIDTH / 4, HEIGHT / 4, WIDTH / 2, HEIGHT / 2 };
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect);

}
