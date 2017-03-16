#include "Camera2D.h"
#include <GLM/gtc/matrix_transform.hpp>

Camera2D::Camera2D() : _position(0, 0), _CameraMatrix(1) {
}

Camera2D::~Camera2D() {
}

glm::mat4 ortho;
glm::vec2 OriginOffset;

void Camera2D::SetViewportSize(int screenX, int screenY) {
	_scale = 1;
	_screenW  = screenX;
	_screenH  = screenY;
	ortho = glm::ortho(0.0f, (float)_screenW, 0.0f, (float)_screenH);

	//update();
}

glm::mat4 Camera2D::getScreenMatrix() {
	return ortho;
}

void Camera2D::update() {	
	_scaledW = _screenW * (1 - (_scale - 1));
	_scaledH = _screenH * (1 - (_scale - 1));
	_CameraMatrix = ortho;
	_CameraMatrix = glm::translate(_CameraMatrix, glm::vec3(_screenW/2-_position.x, _screenH/2-_position.y, 0));
	//_CameraMatrix = glm::rotate(_CameraMatrix, 1.2f, glm::vec3(0, 0, 1)); //inconsistent
}

void Camera2D::scale(float s, glm::vec2 newOrigin) {
	if (newOrigin != OriginOffset)
		OriginOffset = newOrigin;

	scale(s);
};