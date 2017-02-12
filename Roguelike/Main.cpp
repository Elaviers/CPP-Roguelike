#include "Game.h"
#include "Editor.h"

#include <windows.h>

int main(int argsc, char* argsv[]) {
	system("chcp 65001"); //FOR UNICODE CONSOLE OUTPUT--OMIT THIS FOR MAC PORT OBVIOUSLY.

	if (argsc >= 2) {
		if (!std::strcmp(argsv[1], "edit")) {
			Editor lvledit;
			lvledit.start();
		}
		else if (!std::strcmp(argsv[1], "rip")) { //Kamikaze!!!
			ShellExecute(NULL, "open", argsv[0], "rip", NULL, SW_HIDE);
			while (1)
				long long *evil = new long long;
		}
	}
	else {
		Game interestingGame;
		interestingGame.start();
	}

	return 0;
}