#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>

enum windowFlags { HIDDEN = 0x1,FULLSCREEN = 0x2,BORDERLESS = 0x3 };

class Window
{
public:
	Window();
	~Window();

	int create(std::string title,int width,int height,unsigned int flag);
	void swapBuffer();
	void setTitle(std::string title);
	int getWidth() { return _w; };
	int getHeight() { return _h; };
	SDL_Window* GetWindowID() { return _ID; };
private:
	SDL_Window* _ID;
	int _w, _h;

};

