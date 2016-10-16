#pragma once
#include <Engine/Sprite.h>
#include <Engine/Camera2D.h>

class Player {
	public:
		void init(float x,float y,float w,float h);
		void updateCursorLocation(float x,float y);
		void render(GLSLShading shader,Camera2D,float);
private:
	Sprite _crosshair;
	float _angle;
};