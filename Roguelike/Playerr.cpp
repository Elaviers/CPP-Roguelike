#include "Playerr.h"
#include "Game.h"


Playerr::Playerr()
{

}


Playerr::~Playerr()
{

}

void Playerr::mousestate(int mouseX, int mouseY)
{
		SDL_GetMouseState(&mouseX, &mouseY);

	}
