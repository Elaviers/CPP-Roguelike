#include "Camera.h"

#include <GLM/gtc/matrix_transform.hpp>

Camera::Camera() : _position{ 0, 0 }, _CameraMatrix(1) {
}

Camera::~Camera() {
}

glm::mat4 ortho;
Vector2f OriginOffset;

void Camera::setPosition(const Vector2f position) {
	_position = position; 
	update();
}

void Camera::move(const float x,const float y) {
	setPosition(Vector2f{ _position.x + x, _position.y + y });
}

void Camera::SetViewportSize(const int screenX, const int screenY) {
	_scale = 1;
	_screenW  = screenX;
	_screenH  = screenY;
	ortho = glm::ortho(0.0f, (float)_screenW, 0.0f, (float)_screenH);

	//update();
}

glm::mat4 Camera::getScreenMatrix() {
	return ortho;
}

void Camera::update() {	
	_scaledW = _screenW * (1 - (_scale - 1));
	_scaledH = _screenH * (1 - (_scale - 1));
	_CameraMatrix = ortho;
	_CameraMatrix = glm::translate(_CameraMatrix, glm::vec3(_screenW / 2 - _position.x, _screenH / 2 - _position.y, 0));
}

void Camera::scale(const float s, const Vector2f newOrigin) {
	if (newOrigin != OriginOffset)
		OriginOffset = newOrigin;

	scale(s);
};
