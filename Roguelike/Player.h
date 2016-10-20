#pragma once
#include <Engine/Sprite.h>
#include <Engine/Camera2D.h>
#include <SDL/SDL.h>

#include "Projectile.h"

class Player
{
private:
	Sprite _crosshair,_pointer;
	std::vector<Projectile> _projectiles;//Vector of all projectiles to be rendered

	int _moveX,_moveY;//Player axis movement
	float _lastShot;//Time (milliseconds after game start) when the last shot was fired
	bool _shooting;//Whether the player is shooting or not
	std::string tex;

	//variables
	float fireRate;//Fire rate in shots per second
	float moveSpeed;//Movement speed in pixels per second
public:
	Player() : fireRate(.125), moveSpeed(420) {};

	void init(int XPosition,int YPosition,int Size,int CrosshairSize,std::string CrosshairTexture, std::string PointerTexture);
	int mouseX,mouseY;

	void update(float gameTime,float);
	void render(Camera2D& Camera,float DeltaTime);

	void keyUp(SDL_Event a);
	void keyDown(SDL_Event a);
	void setShooting(bool state) { _shooting = state; };
	void shoot();
};