#pragma once
#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <string>
#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"
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
	void setOrigin(float x,float y);//Sets the origin of the sprite. For each axis, 0 is the centre,-1 is left edge, and 1 is right edge. Only affects location for now.
	void setPosition(float x, float y);
	void setRotation(float angle);
	void setColour(GLbyte r, GLbyte g, GLbyte b, GLbyte a);
	void move(float x,float y);
	void swapUVs(int textureIndex);
	void render();
	//void renderToBatch(SpriteBatch &batch);

	GLuint getTextureID() { return _texture.ID; };
private:
	bool _static;
	GLuint _vboID, _vaoID;
	Texture _texture;

	float _xOffset, _yOffset;
	
	void setVAO();
	void updateVertices();
	void setUVS(float,float,float,float);
};

