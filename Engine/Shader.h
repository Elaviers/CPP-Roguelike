#pragma once

#include <GL/glew.h>
#include <GLM/glm.hpp>
#include "ShaderPresets.h"


namespace ShaderPreset { enum ShaderPreset { SPRITE, TRANSFORM_SPRITE, FONT, LINE }; }

class Shader
{
public:
	Shader();
	~Shader();

	void compile(const char* frag,const char* vert);
	void loadPreset(ShaderPreset::ShaderPreset preset);
	void link();
	void addAttribute(const char* attributeName);
	GLuint getUniformLocation(const char* uniformName);
	void useProgram();
	void unUseProgram();

	void set1i(const char* name, int value);
	void set1f(const char* name, float value);
	void set2f(const char* name, float,float);
	void set4f(const char*name,float,float,float,float);
	void setMat4(const char* name,glm::mat4);

private:
	int _attributeCount;
	GLuint _programID,_vertID,_fragID;

	void generateShaderStuff();
	void loadFromFile(const char* dir,GLuint);
	void load(const char* dir,GLuint ID);
};

