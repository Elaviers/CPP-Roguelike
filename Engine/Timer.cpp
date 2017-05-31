#include "Timer.h"

#include <SDL/SDL_timer.h>

void Timer::init(int cVal) {
	setFPSCap(cVal);
}

void Timer::begin() {
	_start = SDL_GetTicks();
}

void Timer::end() {
	_frametime = SDL_GetTicks() - _start;

	deltaTime = _frametime / 1000.f;

	if (_CAP > 0 && _frametime < 1000.f / _CAP) {
		SDL_Delay(1000 / _CAP - _frametime);
		deltaTime += (1000.f / _CAP - _frametime) / 1000.f;
	}
}

float Timer::getFramerate() {
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
