#pragma once

#include <GL/glew.h>
#include <GLM/glm.hpp>

class Shader
{
public:
	Shader();
	~Shader();

	void compile(const char* frag,const char* vert);
	void link();
	void addAttribute(const char* attributeName);
	GLuint getUniformLocation(const char* uniformName);
	void useProgram();
	void unUseProgram();

	void set1i(const char* name, int value);
	void set1f(const char* name, float value);
	void set2f(const char* name, float,float);
	void setMat4(const char* name,glm::mat4);

private:
	int _attributeCount;
	GLuint _programID,_vertID,_fragID;

	void load(const char* dir,GLuint ID);
};

