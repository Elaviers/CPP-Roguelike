#include "Editor.h"
#include "Game.h"
#include "GameData.h"

#include <stdlib.h>
#include <time.h>
#include <windows.h>

int main(int argsc, char* argsv[]) {
	unsigned int t = (unsigned int)time(NULL);
	srand(t);

	printf("%d -> %d\n",(signed char) -120,(unsigned char) -120);

	printf("%s (seeded with %d)\n", argsv[0], t);
	system("chcp 65001"); //FOR UNICODE CONSOLE OUTPUT--OMIT THIS FOR MAC PORT OBVIOUSLY.

	if (argsc >= 2) {
		if (!std::strcmp(argsv[1], "edit")) {
			Editor lvledit;
			lvledit.start();
		}
		else if (!std::strcmp(argsv[1], "rip")) { //Kamikaze!!!
			ShellExecute(NULL, "open", argsv[0], "rip", NULL, SW_HIDE);
			long long* evil;
			while (1)
				evil = new long long[1000];
		}
	}
	else {
		GameData::exedir = argsv[0];
		Game interestingGame;
		interestingGame.start();
	}

	return 0;
}
