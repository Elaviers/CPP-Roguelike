#pragma once
#include <SDL/SDL_video.h>
#include <string>

class Window
{
public:
	Window();
	~Window();

	int create(std::string title, int width, int height, unsigned int flag);
	void swapBuffer();
	void setTitle(std::string title);
	int getWidth() { return _w; };
	int getHeight() { return _h; };
	SDL_Window* GetWindowID() { return _ID; };
	void useContext();
private:
	SDL_GLContext _context;
	SDL_Window* _ID;
	int _w, _h;

};
