#include "Game.h"
#include "Editor.h"

int main(int argsc, char* argsv[]) {
	system("chcp 65001"); //FOR UNICODE CONSOLE OUTPUT--OMIT THIS FOR MAC PORT OBVIOUSLY.

	if (argsc >= 2 && !std::strcmp(argsv[1],"edit")) {
		Editor lvledit;
		lvledit.start();
	}
	else {
		Game interestingGame;
		interestingGame.start();
	}

	return 0;
}