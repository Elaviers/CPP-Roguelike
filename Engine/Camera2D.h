#pragma once
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

class Camera2D
{
public:
	Camera2D();
	~Camera2D();

	void setPosition(glm::vec2 newPosition) { _position = newPosition; _hasChanged = true; };
	void move(float x, float y) { setPosition(glm::vec2(_position.x + x, _position.y + y)); };
	glm::vec2 getPosition() { return _position; };
	void setAngle(float angle) { _angle = angle; _hasChanged = true; };
	float getAngle() { return _angle; };
	void setScale(float s) { _scale = s; _hasChanged = true; };
	float getScale() { return _scale; };
	glm::mat4 getCameraMatrix() { return _CameraMatrix; };
	glm::mat4 getScreenMatrix();

	void init(int screenWidth, int screenHeight);
	void update();

private:
	bool _hasChanged;
	float _scale,_angle;
	int _screenW, _screenH;
	glm::vec2 _position;
	glm::mat4 _CameraMatrix;
};

