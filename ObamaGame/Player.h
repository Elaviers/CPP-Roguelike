#pragma once
#include <Engine/GLSLShading.h>
#include <Engine/Texture.h>
#include <Engine/Sprite.h>
#include <Engine/Camera2D.h>
#include <SDL/SDL_keyboard.h>
#include <GLM/glm.hpp>

class Player
{
public:
	Player();
	~Player();

	void init(float x,float y);
	void render(Shader shader,Camera2D &camera,float deltaTime);
	void keyDown(SDL_Keycode scancode);
	void keyUp(SDL_Keycode scancode);
private:
	int _playerDirection;
	Sprite _playerSprite;
	Camera2D* _cam;

	void handleDirection(bool,bool,bool,bool,bool);
};