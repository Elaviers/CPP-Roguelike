#pragma once
#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <string>
#include "Vertex.h"
#include "Texture.h"
#include "GLSLShading.h"
#include "SpriteBatch.h"

class Sprite
{
public:
	Sprite();
	Sprite(int);
	~Sprite();

	bool dbg;
	int UVGridDivisions;
	float x, y, width, height, rotation;
	Vertex vertices[6];

	void init(float x, float y, float width, float height,bool isStatic = true, std::string texturePath = "");
	void setPosition(float x, float y);
	void swapUVs(int textureIndex);
	void render(GLSLShading shader, glm::mat4 cMat);
	void render(GLSLShading shader);
	void render();
	void renderToBatch(SpriteBatch &batch);

	GLuint getTextureID() { return _texture.ID; };
private:
	float _LastUpdatedRotation;
	bool _static;
	GLuint _vboID;
	Texture _texture;
	glm::vec4 _uvdata;
	
	void updateVertices();
	void setUVS(float,float,float,float);
};

