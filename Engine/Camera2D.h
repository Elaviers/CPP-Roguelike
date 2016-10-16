#pragma once
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

class Camera2D
{
public:
	Camera2D();
	~Camera2D();

	void setPosition(glm::vec2 newPosition) { _position = newPosition; _hasChanged = true; };
	glm::vec2 getPosition() { return _position; };
	void setScale(float s) { _scale = s; _hasChanged = true; };
	float getScale() { return _scale; };
	glm::mat4 getCameraMatrix() { return _CameraMatrix; };

	void init(int screenWidth, int screenHeight);
	void update();

private:
	bool _hasChanged;
	float _scale;
	int _screenW, _screenH;
	glm::vec2 _position;
	glm::mat4 _CameraMatrix;
};

