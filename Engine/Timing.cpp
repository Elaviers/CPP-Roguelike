#include "Timing.h"


void Timing::init(int cVal) {
	setFPSCap(cVal);
}

void Timing::begin() {
	_start = SDL_GetTicks();
}

void Timing::end() {
	_frametime = SDL_GetTicks() - _start;
	deltaTime = (float)_frametime / 1000;
	if (_CAP > 0 && 1000.0f / _CAP > _frametime) {
		deltaTime += (1000.0f / _CAP - _frametime) / 1000;
		SDL_Delay(1000 / _CAP - _frametime);
	}
}

float Timing::getFramerate() {
	static const int avg = 10;
	static int frameTimes[avg], index = 0;

	static int prevTicks = SDL_GetTicks();
	int currentTicks = SDL_GetTicks();

	frameTimes[index % avg] = currentTicks - prevTicks;

	prevTicks = currentTicks;

	int count;

	index++;

	if (index < avg)
		count = index;
	else
		count = avg;

	float FrameAverage = 0;
	for (int i = 0; i < count; i++)
		FrameAverage += frameTimes[i];
	FrameAverage /= count;

	if (FrameAverage > 0)
		return 10000 / FrameAverage;
	
	return (float)_CAP;
}