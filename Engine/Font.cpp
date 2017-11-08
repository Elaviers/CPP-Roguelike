#include "Font.h"

#include "ErrorHandling.h"
#include "Shader.h"
#include "Vertex.h"
#include <GL/glew.h>

Font::Font()
{
}


Font::~Font()
{
}

void Font::init(FT_Library& lib,const char* path, int size) {
	if (FT_New_Face(lib, path, 0, &_face))error("I could not load a font, noooooooob\a\a\a\a!!!");

	_pointsize = size;
	FT_Set_Pixel_Sizes(_face, 0, size);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (int i = 0; i < 128; i++) {//Generate 128 glyphs and insert to character map
		if (FT_Load_Char(_face, i, FT_LOAD_RENDER))
		{
			std::printf("Oi!I couldn't load one of these glyphs!\n");
			continue;
		}

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D,0, GL_RED,
			_face->glyph->bitmap.width,_face->glyph->bitmap.rows,0,
			GL_RED,GL_UNSIGNED_BYTE,_face->glyph->bitmap.buffer);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character character = {
			texture,
			glm::ivec2(_face->glyph->bitmap.width, _face->glyph->bitmap.rows),
			glm::ivec2(_face->glyph->bitmap_left, _face->glyph->bitmap_top),
			(GLuint)_face->glyph->advance.x
		};
		_chars.insert(std::pair<GLchar, Character>(i, character));
	}
	glBindTexture(GL_TEXTURE_2D,0);

	FT_Done_Face(_face);
	//Remember to call FT_Done_Freetype after initialising all fonts!

	glGenVertexArrays(1,&_vao);
	glGenBuffers(1, &_vbo);

	glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER,_vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*6, NULL, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));		//0-position
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));				//2-uvs
		glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);

	loaded = true;
}

void Font::drawString(const String& text, float x, float y, int s, glm::vec4 colour, Shader &shader) {
	shader.set4f("TextColour",colour.r, colour.g, colour.b, colour.a);
	drawString(text, x, y, (float)s / _pointsize);
}

void Font::drawString(const String& text, float xp, float y, float size) {
	glBindVertexArray(_vao);

	float x = xp;

	for (const char* c = text.getData(); *c != '\0'; ++c)
	{
		Character ch = _chars[*c];

		GLfloat w = ch.Size.x * size;
		GLfloat h = ch.Size.y * size;

		GLfloat xpos = x + ch.Bearing.x * size;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * size;

		// Update VBO for each character
		Vertex vertices[6];
		vertices[0].setPosition(xpos,		ypos + h);	vertices[0].setUv(0,1);
		vertices[1].setPosition(xpos + w,	ypos);		vertices[1].setUv(1,0);
		vertices[2].setPosition(xpos,		ypos);		vertices[2].setUv(0,0);
		vertices[3].setPosition(xpos,		ypos + h);	vertices[3].setUv(0,1);
		vertices[4].setPosition(xpos + w,	ypos + h);	vertices[4].setUv(1,1);
		vertices[5].setPosition(xpos + w,	ypos);		vertices[5].setUv(1,0);

		glBindTexture(GL_TEXTURE_2D, ch.TextureID);

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		x += (ch.Advance >> 6) * size; // Bitshift to pixel value
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
