#include "Camera2D.h"
#include <GLM/gtc/matrix_transform.hpp>

Camera2D::Camera2D() : _position{ 0, 0 }, _CameraMatrix(1) {
}

Camera2D::~Camera2D() {
}

glm::mat4 ortho;
Vector2f OriginOffset;

void Camera2D::setPosition(const Vector2f position) {
	_position = position; 
	update();
}

void Camera2D::move(const float x,const float y) {
	setPosition(Vector2f{ _position.x + x, _position.y + y });
}

void Camera2D::SetViewportSize(const int screenX, const int screenY) {
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

void Camera2D::scale(const float s, const Vector2f newOrigin) {
	if (newOrigin != OriginOffset)
		OriginOffset = newOrigin;

	scale(s);
};