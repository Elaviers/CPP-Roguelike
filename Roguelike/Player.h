#pragma once
#include "Level.h"

#include <Engine/Camera2D.h>
#include <Engine/Entity.h>
#include <Engine/Rect.h>
#include <Engine/Sprite.h>
#include <SDL/SDL_events.h>
#include <string>

class Player : public Entity
{
private:
	Sprite _crosshair,_playerSprite;

	int _moveX,_moveY;//Player axis movement
	float _lastShot;//Time (milliseconds after game start) when the last shot was fired
	bool _shooting;//Whether the player is shooting or not
	std::string tex;
	
	//variables
	float fireRate;//Fire rate in shots per second
	float moveSpeed;//Movement speed in pixels per second
public:
	Player() : _moveX(0), _moveY(0), _lastShot(0), _shooting(false), fireRate(.125), moveSpeed(420) {};
	~Player() {};

	Rect collision;

	void init(int XPosition,int YPosition,int Size,int CrosshairSize,std::string CrosshairTexture, std::string PointerTexture);

	void update(float DeltaTime) override;
	void render(Shader& s) override;

	void keyUp(SDL_Event a);
	void keyDown(SDL_Event a);
	void setShooting(bool state) { _shooting = state; };
	void shoot();

};
