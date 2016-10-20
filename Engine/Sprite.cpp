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
	if (_vaoID != 0)
		glDeleteVertexArrays(1, &_vaoID);
}

#include <iostream>
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
	if (_vaoID == 0)
		glGenVertexArrays(1, &_vaoID);

	swapUVs(0);
}

void Sprite::setVAO() {
	glBindVertexArray(_vaoID);//bind Vertex Array Object
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);//bind Vertex Buffer Object
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, _static ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);		//Update buffer data
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));		//0-position
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour));	//1-colour
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));				//2-uvs
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);//unbind Vertex Buffer Object
	glBindVertexArray(0);//unbind Vertex Array Object
}

void Sprite::render() {
	glActiveTexture(GL_TEXTURE_2D);
	//std::cout << "Bind texture...";
	_texture.bind();
	//std::cout << "Bind vao...";
	glBindVertexArray(_vaoID);
	//std::cout << "Draw...";
	glDrawArrays(GL_TRIANGLES, 0, 6);
	//std::cout << "Unbind vao!\n";
	glBindVertexArray(0);

	glActiveTexture(0);
}

void Sprite::updateVertices() {
	if (dbg) std::cout << "updating...\n";

	float rSin = glm::sin(glm::radians(rotation)), rCos = glm::cos(glm::radians(rotation));
	float x1 = -width / 2.0f, y1 = -height / 2.0f;
	float x2 = width / 2.0f, y2 = height / 2.0f;
	float offsetX = x + x2 + _xOffset, offsetY = y + y2 + _yOffset;

	vertices[0].setPosition(x2 * rCos - y2 * rSin + offsetX, x2 * rSin + y2 * rCos + offsetY);
	vertices[1].setPosition(x1 * rCos - y2 * rSin + offsetX, x1 * rSin + y2 * rCos + offsetY);
	vertices[2].setPosition(x1 * rCos - y1 * rSin + offsetX, x1 * rSin + y1 * rCos + offsetY);
	vertices[3].setPosition(x1 * rCos - y1 * rSin + offsetX, x1 * rSin + y1 * rCos + offsetY);
	vertices[4].setPosition(x2 * rCos - y1 * rSin + offsetX, x2 * rSin + y1 * rCos + offsetY);
	vertices[5].setPosition(x2 * rCos - y2 * rSin + offsetX, x2 * rSin + y2 * rCos + offsetY);

	setVAO();
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
		setUVS(UVx,UVy,inc,inc);
	}
	else {
		setUVS(UVx+inc, UVy, -inc, inc);
	}
}

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

void Sprite::setColour(GLbyte r, GLbyte g, GLbyte b, GLbyte a) {

	for (int i = 0; i < 6; i++)
		vertices[i].setColour(r, g, b, a);

}

//void Sprite::renderToBatch(SpriteBatch &batch) {
//	batch.render(glm::vec4(x, y, width, height), _uvdata, _texture.ID, 0, Vertex::colourOf(255,255,255,255));
//}