#pragma once
#include "Vertex.h"
#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <vector>

enum class sortType {
	NONE,
	ASCENDING,
	DESCENDING,
	TEXTURE
};

struct Glyph
{
	Vertex bottomLeft,topLeft,bottomRight,topRight;
	GLuint textureID;
	float depth;
};

class Batch {
public:
	Batch(GLuint OFFSET, GLuint VERTCOUNT, GLuint TEXTUREID) :	offset(OFFSET), 
																vertCount(VERTCOUNT), 
																textureID(TEXTUREID) {}
	GLuint offset, vertCount, textureID;
};

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	void init();
	void begin(sortType type = sortType::TEXTURE);
	void end();
	void render(const glm::vec4 &pos,const glm::vec4 &uvCoords,GLuint textureID,float depth,const Colour &colour);
	void renderBatch();
private:
	GLuint _VBO,_VAO;
	std::vector<Glyph*> _glyphs;
	std::vector<Batch> _batches;
	sortType _sortType;

	static bool compareAsc(Glyph* a, Glyph* b) { return a->depth < b->depth; };
	static bool compareDesc(Glyph* a, Glyph* b) { return a->depth > b->depth; };
	static bool compareTex(Glyph* a, Glyph* b) { return a->textureID < b->textureID; };

	void createBatches();
	void createVAO();
	void sortGlyphs();
};
