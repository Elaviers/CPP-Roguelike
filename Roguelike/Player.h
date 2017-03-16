#pragma once
#include <Engine/Sprite.h>
#include <Engine/Camera2D.h>
#include <Engine/GameObject.h>
#include "Level.h"
#include <SDL/SDL.h>
#include <vector>
#include "Projectile.h"

class Player : public GameObject
{
private:
	Sprite _crosshair,_playerSprite;
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

	void update() override;
	void render(Shader& s,float dt) override;

	void keyUp(SDL_Event a);
	void keyDown(SDL_Event a);
	void setShooting(bool state) { _shooting = state; };
	void shoot();

	void setPointerLocation(float x,float y);
};