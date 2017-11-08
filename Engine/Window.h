#pragma once
#include <SDL/SDL_video.h>

class Window
{
public:
	Window();
	~Window();

	int create(const char* title, int width, int height, unsigned int flag);
	void swapBuffer();
	void setTitle(const char* title);
	int getWidth() { return _w; };
	int getHeight() { return _h; };
	SDL_Window* GetWindowID() { return _ID; };
	void useContext();
private:
	SDL_GLContext _context;
	SDL_Window* _ID;
	int _w, _h;

};
