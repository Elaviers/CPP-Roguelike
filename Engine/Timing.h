#pragma once
#include <SDL/SDL.h>

class Timing
{
public:
	void init(int FPSCAP = -1);
	void setFPSCap(int value) { _CAP = value; };
	void begin();
	void end();
	float getFramerate();
	float deltaTime;
private:
	int _CAP;
	int _start,_frametime;
};
