#include <cstddef>
#include <stdlib.h> 
#include "Sprite.h"
#include "ResourceManager.h"
#include <GLM/glm.hpp>

Sprite::Sprite() : _vboID(0), UVGridDivisions(1) {
}

Sprite::Sprite(int divisions) : _vboID(0) {
	UVGridDivisions = divisions;
}


Sprite::~Sprite() {
	if (_vboID != 0)
		glDeleteBuffers(1, &_vboID);
}

void Sprite::init(float xp, float yp,float w,float h,bool isStatic,std::string path) {
	_static = isStatic;
	x = xp;
	y = yp;
	width = w;
	height = h;

	dbg = false;

	if (path != "")_texture = ResourceManager::getTexture(path);
	else _texture.ID = 0;

	if (_vboID == 0)
		glGenBuffers(1, &_vboID);

	for (int i = 0; i < 6; i++)
		vertices[i].setColour(255,255,255,255);

	swapUVs(0);
}

void Sprite::render(GLSLShading shader, glm::mat4 cMat) {
	GLint textureLocation = shader.getUniformLocation("sTexture");
	glUniform1i(textureLocation, 0);

	GLint matLocation = shader.getUniformLocation("p");
	glUniformMatrix4fv(matLocation, 1, GL_FALSE, &(cMat[0][0]));

	render();
}

void Sprite::render(GLSLShading shader) {
	GLint textureLocation = shader.getUniformLocation("sTexture");
	glUniform1i(textureLocation, 0);

	render();
}

void Sprite::render() {
	glBindTexture(GL_TEXTURE_2D, _texture.ID);
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, colour));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::setOrigin(float offsetx,float offsety) {
	_xOffset = -width/2 * (offsetx + 1);
	_yOffset = -height/2 * (offsety + 1);
	updateVertices();
}

void Sprite::setPosition(float xp,float yp) {
	if (x == xp && y == yp)return;
	x = xp; y = yp;
	updateVertices();
}

void Sprite::move(float xp,float yp) {
	if (!(xp == 0 && yp == 0))setPosition(x+xp,y+yp);
}

void Sprite::swapUVs(int textureIndex) {
	if (UVGridDivisions <= 1) {
		setUVS(0, 0, 1, 1);
		return;
	}

	bool flipped = false;
	if (textureIndex < 0) {
		textureIndex *= -1;
		flipped = true;
	}

	float inc = 1.0f / UVGridDivisions;
	float UVx = 0, UVy = UVGridDivisions-1.0f;

	while (textureIndex > (UVGridDivisions - 1)) {
			UVy-=1;
			textureIndex -= UVGridDivisions;
		}

	UVx = (float)textureIndex / (float)UVGridDivisions;
	UVy /= UVGridDivisions;

	if (!flipped) {
		_uvdata = glm::vec4(UVx,UVy,inc,inc);
	}
	else {
		_uvdata = glm::vec4(UVx+inc, UVy, -inc, inc);
	}

	setUVS(_uvdata.x,_uvdata.y,_uvdata.z,_uvdata.w);
}
#include <iostream>
void Sprite::setUVS(float startX,float startY,float UVwidth,float UVheight) {
	vertices[0].setUv(startX + UVwidth, startY + UVheight);
	vertices[1].setUv(startX, startY + UVheight);
	vertices[2].setUv(startX, startY);
	vertices[3].setUv(startX, startY);
	vertices[4].setUv(startX + UVwidth, startY);
	vertices[5].setUv(startX + UVwidth, startY + UVheight);
	updateVertices();
}

void Sprite::setRotation(float a) {
	rotation = a;
	updateVertices();
}

void Sprite::updateVertices() {
	if (dbg) std::cout << "updating...\n";

	float rSin = glm::sin(glm::radians(rotation)), rCos = glm::cos(glm::radians(rotation));
	float x1 = -width/2.0f, y1 = -height/2.0f;
	float x2 = width / 2.0f, y2 = height / 2.0f;
	float offsetX = x + x2 + _xOffset, offsetY = y + y2 + _yOffset;

	vertices[0].setPosition(x2 * rCos - y2 * rSin + offsetX,x2 * rSin + y2 * rCos + offsetY);
	vertices[1].setPosition(x1 * rCos - y2 * rSin + offsetX,x1 * rSin + y2 * rCos + offsetY);
	vertices[2].setPosition(x1 * rCos - y1 * rSin + offsetX,x1 * rSin + y1 * rCos + offsetY);
	vertices[3].setPosition(x1 * rCos - y1 * rSin + offsetX,x1 * rSin + y1 * rCos + offsetY);
	vertices[4].setPosition(x2 * rCos - y1 * rSin + offsetX,x2 * rSin + y1 * rCos + offsetY);
	vertices[5].setPosition(x2 * rCos - y2 * rSin + offsetX,x2 * rSin + y2 * rCos + offsetY);

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, _static ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::renderToBatch(SpriteBatch &batch) {
	batch.render(glm::vec4(x, y, width, height), _uvdata, _texture.ID, 0, Vertex::colourOf(255,255,255,255));
}