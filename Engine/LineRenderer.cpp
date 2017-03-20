#include "LineRenderer.h"

std::vector<LineRenderer::VertexNoUV> LineRenderer::_vertices;
GLuint LineRenderer::_vbo, LineRenderer::_vao;
Shader LineRenderer::_shader;

bool initialised = false;

void LineRenderer::init() {
	glGenVertexArrays(1,&_vao);
	glGenBuffers(1,&_vbo);

	std::printf("LineRenderer initialised (VAO:%d VBO:%d)\n", _vao, _vbo);

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER,_vbo);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexNoUV), (void*)offsetof(VertexNoUV, Position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexNoUV), (void*)offsetof(VertexNoUV, Colour));


	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);

	_shader.loadPreset(ShaderPreset::LINE);
	_shader.link();

	initialised = true;
}

void LineRenderer::addLine(float x, float y, float x2, float y2, Colour c) {
	int i = (int)_vertices.size();
	_vertices.resize(_vertices.size() + 2);

	_vertices[i].Position = glm::vec2(x,y);
	_vertices[i].Colour = c;
	_vertices[i + 1].Position = glm::vec2(x2,y2);
	_vertices[i + 1].Colour = c;

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER,_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexNoUV) * _vertices.size(), nullptr, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexNoUV) * _vertices.size(),_vertices.data());
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
}

void LineRenderer::clear() {
	_vertices.clear();
}

void LineRenderer::render(Camera2D& c) {
	if (initialised) {
		_shader.useProgram();
		_shader.setMat4("projection", c.getCameraMatrix());
		glBindVertexArray(_vao);
		glDrawArrays(GL_LINES, 0, (GLsizei)_vertices.size());
		glBindVertexArray(0);
		_shader.unUseProgram();
	}
}