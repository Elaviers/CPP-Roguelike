#pragma once
#include <GL/glew.h>
#include <string>
#include "Vertex.h"
#include "Texture.h"

namespace CornerEnum {
	enum CornerEnum {TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};
}

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

	void init(float x, float y, float width, float height,bool isStatic = true, const std::string& texturePath = "");//Creates sprite,binds VAO,VBO, and texture
	void setOrigin(float x,float y);//Sets the origin of the sprite. For each axis, 0 is the centre,-1 is left edge, and 1 is right edge. Only affects location for now.
	void setPosition(float x, float y);//Sets position
	void setRotation(float angle);//Sets Z angle
	void setColour(GLbyte r, GLbyte g, GLbyte b, GLbyte a);//Sets colour
	void move(float x,float y);//Moves sprite
	void swapUVs(int textureIndex);//Swap to another index location on a splitted spritesheet, starting at 0 and ending at UVGridDivisions^2-1
	void render();//Renders the sprite. Call from within a shader program!

	Vector2f getCorner(int index);
	Vector2f getCentre();

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

