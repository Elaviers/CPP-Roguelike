#include "Camera2D.h"

Camera2D::Camera2D() : _position(0, 0), _CameraMatrix(1), _scale(1) {
}

Camera2D::~Camera2D() {
}

glm::mat4 ortho;
glm::vec2 OriginOffset;

void Camera2D::SetViewportSize(int screenX, int screenY) {
	_screenW = screenX;
	_screenH = screenY;
	ortho = glm::ortho(0.0f, (float)_screenW, 0.0f, (float)_screenH);
}

glm::mat4 Camera2D::getScreenMatrix() {
	return ortho;
}

void Camera2D::update() {
	_CameraMatrix = glm::translate(ortho, glm::vec3(-_position.x, -_position.y, 0));
	_CameraMatrix = glm::rotate(_CameraMatrix, _angle, glm::vec3(1, 0, 0));
	_CameraMatrix = glm::scale(_CameraMatrix, glm::vec3(_scale, _scale, 0));
	_CameraMatrix = glm::translate(_CameraMatrix, glm::vec3(_screenW * (1 - (_scale - 1)) / 2, _screenH * (1 - (_scale - 1)) / 2, 0));
}

void Camera2D::scale(float s, glm::vec2 newOrigin) {
	if (newOrigin != OriginOffset)
		OriginOffset = newOrigin;

	scale(s);
};