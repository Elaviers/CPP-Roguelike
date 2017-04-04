#pragma once
#include "Vector2f.h"

#include <GLM/mat4x4.hpp>

class Camera2D
{
public:
	Camera2D();
	~Camera2D();

	void setPosition(Vector2f newPosition);	//Sets position (vec2)
	void move(float x, float y);	//Moves camera
	Vector2f getPosition() const { return _position; }; //Returns current position

	void setAngle(float angle) { _angle = angle; update(); }; //Sets Z rotation
	float getAngle() const { return _angle; }; //Returns Z rotation

	void setScale(float s) { _scale = s; update(); }; //Sets scale
	void scale(float s) { setScale(s + _scale); }; //Adds to scale
	void scale(float s, Vector2f newOrigin);	//Adds to scale and scales based on a certain point
	float getScale() const { return _scale; }; //Returns scale

	Vector2f getMin() const { return Vector2f{ _position.x - _screenW / 2, _position.y - _screenH / 2 }; }
	Vector2f getMax() const { return Vector2f{ _position.x + _screenW / 2, _position.y + _screenH / 2 }; }

	glm::mat4 getCameraMatrix() const { return _CameraMatrix; }; //Returns the camera matrix
	glm::mat4 getScreenMatrix(); //Returns the normalised matrix

	int getWidth() { return _screenW; };
	int getHeight() { return _screenH; };

	void SetViewportSize(int screenWidth, int screenHeight); //Sets width and height of the viewport (does NOT use GLViewport!)

	Vector2f screentoWorld(int x, int y) const {
		float scaleFactor = 1 - (_scale - 1);

		return Vector2f {
			_position.x - (_screenW * scaleFactor / 2) + (x * scaleFactor),
			_position.y - (_screenH * scaleFactor / 2) + (y * scaleFactor)
		};
	};

private:
	float _scale, _angle;
	int _screenW, _screenH;
	float _scaledW, _scaledH;
	Vector2f _position;
	glm::mat4 _CameraMatrix;

	void update();
};
