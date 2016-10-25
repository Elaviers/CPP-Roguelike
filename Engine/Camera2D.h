#pragma once
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

class Camera2D
{
public:
	Camera2D();
	~Camera2D();

	void setPosition(glm::vec2 newPosition) { _position = newPosition; _hasChanged = true; };	//Sets position (vec2)
	void setPosition(float x, float y)		{ setPosition(glm::vec2(x, y)); };					//Sets position (float)
	void move(float x, float y)				{ setPosition(glm::vec2(_position.x + x, _position.y + y)); };	//Moves camera
	glm::vec2 getPosition()					{ return _position; }; //Returns current position

	void setAngle(float angle)				{ _angle = angle; _hasChanged = true; }; //Sets Z rotation
	float getAngle()						{ return _angle; }; //Returns Z rotation

	void setScale(float s)					{ _scale = s; _hasChanged = true; }; //Sets scale
	void scale(float s)						{  setScale(s + _scale); move(s, s);}; //Adds to scale
	void scale(float s, glm::vec2 newOrigin);	//Adds to scale and scales based on a certain point
	float getScale()						{ return _scale; }; //Returns scale

	glm::mat4 getCameraMatrix() { return _CameraMatrix; }; //Returns the camera matrix
	glm::mat4 getScreenMatrix(); //Returns the normalised matrix

	int getWidth() { return _screenW; };
	int getHeight() { return _screenH; };

	void SetViewportSize(int screenWidth, int screenHeight); //Sets width and height of the viewport (does NOT use GLViewport!)
	void update(); //Will apply any pending changes to the camera

private:
	bool _hasChanged;
	float _scale,_angle;
	int _screenW, _screenH;
	glm::vec2 _position;
	glm::mat4 _CameraMatrix;
};

