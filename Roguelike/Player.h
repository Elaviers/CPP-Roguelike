#pragma once
#include <Engine/Sprite.h>
#include <Engine/Camera2D.h>
#include <Engine/GLSLShading.h>
#include <SDL/SDL.h>

#include "Projectile.h"

class Player
{
private:
	Sprite _crosshair,_pointer;
	std::vector<Projectile> _projectiles;

	int _moveX,_moveY;
	float _lastShot;
	bool _shooting;

	//variables
	float fireRate = 0.125;//Fire rate in shots per second
	float moveSpeed = 420;//Movement speed in pixels per second
public:
	void init(int XPosition,int YPosition,int Size,std::string TexturePath);
	int mouseX,mouseY;

	void update(float gameTime);
	void render(GLSLShading Shader,Camera2D& Camera,float DeltaTime);

	void keyUp(SDL_Event a);
	void keyDown(SDL_Event a);
	void setShooting(bool state) { _shooting = state; };
	void shoot();
};