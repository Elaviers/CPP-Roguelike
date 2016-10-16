#pragma once
#include <Engine/Sprite.h>
#include <Engine/Camera2D.h>
#include <Engine/GLSLShading.h>

class Player
{
private:
	Sprite _sprite;
public:
	void init(int XPosition,int YPosition,int Size,std::string TexturePath);
	int mouseX;
	int mouseY;

	void updateMousePosition();
	void render(GLSLShading Shader,Camera2D& Camera);
};