#include "ErrorHandling.h"

extern void error(std::string errorString) {
	std::cout << "\a *** " << errorString << std::endl << "Enter any key to continue...";
	int a;
	std::cin >> a;
	SDL_Quit();
	exit(1);
}