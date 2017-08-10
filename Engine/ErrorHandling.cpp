#include "ErrorHandling.h"

#include <iostream>
#include <SDL/SDL.h>

extern void error(const std::string& errorString) {
#ifdef _DEBUG
	abort();
#else
	std::cout << "\a *** " << errorString << std::endl;
	int a;
	std::cin >> a;
#endif

	SDL_Quit();
	exit(1);
}
