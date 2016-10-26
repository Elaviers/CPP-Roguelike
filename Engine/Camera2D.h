#pragma once
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

class Camera2D
{
public:
	Camera2D();
	~Camera2D();

	void setPosition(glm::vec2 newPosition) { _position = newPosition; update(); };	//Sets position (vec2)
	void setPosition(float x, float y)		{ setPosition(glm::vec2(x, y)); };					//Sets position (float)
	void move(float x, float y)				{ setPosition(glm::vec2(_position.x + x, _position.y + y)); };	//Moves camera
	glm::vec2 getPosition()					{ return _position; }; //Returns current position

	void setAngle(float angle)				{ _angle = angle; update(); }; //Sets Z rotation
	float getAngle()						{ return _angle; }; //Returns Z rotation

	void setScale(float s)					{ _scale = s; update(); }; //Sets scale
	void scale(float s)						{  setScale(s + _scale);}; //Adds to scale
	void scale(float s, glm::vec2 newOrigin);	//Adds to scale and scales based on a certain point
	float getScale()						{ return _scale; }; //Returns scale

	glm::mat4 getCameraMatrix() { return _CameraMatrix; }; //Returns the camera matrix
	glm::mat4 getScreenMatrix(); //Returns the normalised matrix

	int getWidth() { return _screenW; };
	int getHeight() { return _screenH; };

	void SetViewportSize(int screenWidth, int screenHeight); //Sets width and height of the viewport (does NOT use GLViewport!)

	glm::vec2 screentoWorld(float x, float y) { 
		float scaleFactor = 1 - (_scale - 1);

		return glm::vec2(
		_position.x - (_screenW * scaleFactor / 2) + (x * scaleFactor),
		_position.y - (_screenH * scaleFactor / 2) + (y * scaleFactor)
	); };

private:
	float _scale,_angle;
	int _screenW, _screenH;
	glm::vec2 _position;
	glm::mat4 _CameraMatrix;

	void update();
};

