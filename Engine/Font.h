#pragma once

#include <map>

#include <Gl/glew.h>
#include <glm/glm.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Shader.h"

struct Character {
	GLuint TextureID;
	glm::ivec2 Size;		// Size of glyph
	glm::ivec2 Bearing;		// Offset from baseline to left/top of glyph
	GLuint Advance;			// Horizontal offset to advance to next glyph
};

class Font
{
private:
	FT_Face _face;
	std::map <GLchar, Character> _chars;
	GLuint _vao, _vbo;
public:
	Font();
	~Font();

	void init(FT_Library& lib,const char* path,int);	//Creates an FT Face, creates the character map, and configures texture properties
	void drawString(std::string text,float x,float y);	//Renders a string to the screen. Call from within a shader program!
	void drawString(std::string text, float x, float y, glm::vec4 Colour, Shader s); //Renders a string to the screen. Call from within a shader program!
};

