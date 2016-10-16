#pragma once

#include <GL/glew.h>

class GLSLShading
{
public:
	GLSLShading();
	~GLSLShading();

	void compileShaders(const char* frag,const char* vert);
	void linkShaders();
	void addAttribute(const char* attributeName);
	GLuint getUniformLocation(const char* uniformName);
	void useProgram();
	void unUseProgram();

private:
	int _attributeCount;
	GLuint _programID,_vertID,_fragID;

	void loadShader(const char* dir,GLuint ID);
};

