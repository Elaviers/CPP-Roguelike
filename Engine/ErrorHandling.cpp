#include "ErrorHandling.h"

#include "String.h"
#include <iostream>
#include <SDL/SDL.h>

extern void error(const String& errorString) {
#ifdef _DEBUG
	abort();
#else
	std::cout << "\a *** " << errorString.getData() << std::endl;
	int a;
	std::cin >> a;
#endif

	SDL_Quit();
	exit(1);
}
