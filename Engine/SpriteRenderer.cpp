#include "SpriteRenderer.h"
#include "Vertex.h"
#include "Utility.h"

#include <cstddef>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

SpriteRenderer::SpriteRenderer()
{
}


SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1,&_vao);
}

using namespace glm;

void SpriteRenderer::drawSprite(Shader shader, Texture &t, float x, float y, float width, float height, float angle) {
	mat4 transform;
	transform = translate(transform,vec3(x,y,0));
	
	transform = scale(transform, vec3(width, height, 1));
	
	shader.setMat4("transform",transform);

	glActiveTexture(GL_TEXTURE_2D);
	t.bind();
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glActiveTexture(0);
}

void SpriteRenderer::init() 
{
	Vertex poo[6];

	poo[0].setPosition(0,1);
	poo[1].setPosition(1,0);
	poo[2].setPosition(0,0);
	poo[3].setPosition(0,1);
	poo[4].setPosition(1,1);
	poo[5].setPosition(1,0);

	Utility::sheetUV(poo, 0, 8, 0);

	glGenVertexArrays(1,&_vao);
	glGenBuffers(1, &_vbo);

	glBindVertexArray(_vao);//bind Vertex Array Object
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);//bind Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, sizeof(poo), poo, GL_STATIC_DRAW);		//Update buffer data
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));		//0-position
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour));	//1-colour
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));				//2-uvs
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);//unbind Vertex Buffer Object
	glBindVertexArray(0);//unbind Vertex Array Object
}