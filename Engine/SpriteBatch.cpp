#include "SpriteBatch.h"
#include <algorithm>

SpriteBatch::SpriteBatch() : _VBO(0), _VAO(0) {
}

SpriteBatch::~SpriteBatch() {
}

void SpriteBatch::init() {
	createVAO();
}

void SpriteBatch::begin(sortType type) {
	_sortType = type;
	_batches.clear();
	for (unsigned int i = 0; i < _glyphs.size(); i++)
		delete _glyphs[i];
	_glyphs.clear();
}

void SpriteBatch::end() {
	sortGlyphs();
	createBatches();
}

void SpriteBatch::createBatches() {
	std::vector<Vertex> vertices;
	vertices.resize(_glyphs.size() * 6);

	if (_glyphs.empty())return;

	int vIndex = 0,offset = 0;

	for (unsigned int i = 0; i < _glyphs.size(); i++) {
		if (i == 0 || _glyphs[i]->textureID != _glyphs[i - 1]->textureID)
			_batches.emplace_back(offset, 6, _glyphs[i]->textureID);
		else if (i > 0)
			_batches.back().vertCount += 6;

		vertices[vIndex++] = _glyphs[i]->bottomLeft;
		vertices[vIndex++] = _glyphs[i]->topLeft;
		vertices[vIndex++] = _glyphs[i]->bottomRight;
		vertices[vIndex++] = _glyphs[i]->bottomRight;
		vertices[vIndex++] = _glyphs[i]->topLeft;
		vertices[vIndex++] = _glyphs[i]->topRight;

		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER,_VBO);
	glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(Vertex),nullptr,GL_DYNAMIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER,0,vertices.size() * sizeof(Vertex),vertices.data());

	glBindBuffer(GL_ARRAY_BUFFER,0);
}

void SpriteBatch::createVAO() {
	if (_VAO == 0)
		glGenVertexArrays(1,&_VAO);

	glBindVertexArray(_VAO);

	if (_VBO == 0)
		glGenBuffers(1,&_VBO);

	glBindBuffer(GL_ARRAY_BUFFER,_VBO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, colour));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glBindVertexArray(0);
}

void SpriteBatch::sortGlyphs() {

	switch (_sortType) {
		case sortType::NONE: return;
		case sortType::ASCENDING :
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareAsc);
			break;
		case sortType::DESCENDING:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareDesc);
			break;
		case sortType::TEXTURE:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareTex);
	}
}

void SpriteBatch::render(const glm::vec4 &pos, const glm::vec4 &uvCoords,
						 GLuint textureID, float depth, const Colour &colour) {

	Glyph* g = new Glyph;

	g->textureID = textureID;
	g->depth = depth;

	g->bottomLeft.colour = colour;
	g->bottomLeft.setPosition(pos.x, pos.y);
	g->bottomLeft.setUv(uvCoords.x, uvCoords.y);

	g->topLeft.colour = colour;
	g->topLeft.setPosition(pos.x, pos.y + pos.w);
	g->topLeft.setUv(uvCoords.x, uvCoords.y + uvCoords.w);

	g->bottomRight.colour = colour;
	g->bottomRight.setPosition(pos.x + pos.z, pos.y);
	g->bottomRight.setUv(uvCoords.x + uvCoords.z, uvCoords.y);

	g->topRight.colour = colour;
	g->topRight.setPosition(pos.x + pos.z, pos.y + pos.w);
	g->topRight.setUv(uvCoords.x + uvCoords.z, uvCoords.y + uvCoords.w);

	_glyphs.push_back(g);
}

void SpriteBatch::renderBatch() {

	glBindVertexArray(_VAO);

	for (unsigned int i = 0; i < _batches.size(); i++) {
		glBindTexture(GL_TEXTURE_2D,_batches[i].textureID);
		glDrawArrays(GL_TRIANGLES,_batches[i].offset,_batches[i].vertCount);
	}

	glBindVertexArray(0);
}