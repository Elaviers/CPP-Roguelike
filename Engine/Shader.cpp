#include "Shader.h"

#include "ErrorHandling.h"
#include "RenderType.h"

#include <fstream>
#include <GL/glew.h>
#include <string>
#include <vector>

Shader::Shader() :_attributeCount(0),  _programID(0), _vertID(0), _fragID(0) {
}


Shader::~Shader() {
}

void Shader::generateShaderStuff() {
	_programID = glCreateProgram();

	_vertID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertID == 0)
		error("Vertex shader issues mang");
	_fragID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragID == 0)
		error("Fragment shader issues mang");
}

void Shader::compile(const char* frag, const char* vert) {
	generateShaderStuff();

	loadFromFile(frag, _fragID);
	loadFromFile(vert, _vertID);
}

void Shader::loadPreset(ShaderPreset::ShaderPreset type) {
	switch (type) {
		case ShaderPreset::SPRITE:
			generateShaderStuff();
			load(Presets::SPRITE_FRAG, _fragID);
			load(Presets::SPRITE_VERT, _vertID);
			addAttribute("vertPosition");
			addAttribute("vertColour");
			addAttribute("vertUV");
			Channel = RenderTypes::SPRITE;
			break;
		case ShaderPreset::TRANSFORM_SPRITE:
			generateShaderStuff();
			load(Presets::SPRITE_FRAG, _fragID);
			load(Presets::TRANSFORMED_SPRITE_VERT, _vertID);
			addAttribute("vertPosition");
			addAttribute("vertColour");
			addAttribute("vertUV");
			Channel = RenderTypes::SPRITE;
			break;
		case ShaderPreset::LINE:
			generateShaderStuff();
			load(Presets::LINE_FRAG, _fragID);
			load(Presets::LINE_VERT, _vertID);
			addAttribute("vertPosition");
			addAttribute("vertColour");
			break;
		case ShaderPreset::FONT:
			generateShaderStuff();
			load(Presets::FONT_FRAG, _fragID);
			load(Presets::FONT_VERT, _vertID);
			addAttribute("vertPosition");
			addAttribute("vertUV");
			Channel = RenderTypes::FONT;
			break;
		default:
			error("Invalid preset");
	}
}

void Shader::loadFromFile(const char* path,GLuint ID) {
	std::ifstream ShaderFile(path);
	if (ShaderFile.fail()) {
		perror(path);
		error("Ey gaylord, I couldn't open a shader!\n");
	}

	std::string contents = "", line;

	while (std::getline(ShaderFile, line))
		contents += line + '\n';
	ShaderFile.close();

	const char* readcontents = contents.c_str();
	load(readcontents, ID);
}

void Shader::load(const char* content,GLuint ID) {
	glShaderSource(ID, 1, &content, nullptr);
	glCompileShader(ID);

	GLint success = 0;
	glGetShaderiv(ID, GL_COMPILE_STATUS, &success);

	if (!success) {
		GLint maxlength = 0;
		glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &maxlength);

		std::vector<GLchar> errorLog(maxlength);
		glGetShaderInfoLog(ID, maxlength, &maxlength, &errorLog[0]);

		glDeleteShader(ID);
		std::printf("%s\n", &(errorLog[0]));
		error("Shader compilation error M8");
	}

}

void Shader::link() {
	glAttachShader(_programID, _vertID);
	glAttachShader(_programID, _fragID);
	glLinkProgram(_programID);

	GLint linkSuccess = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, &linkSuccess);

	if (!linkSuccess) {
		GLint maxlength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxlength);

		std::vector<GLchar> errorLog(maxlength);
		glGetProgramInfoLog(_programID, maxlength, &maxlength, &errorLog[0]);

		glDeleteProgram(_programID);
		glDeleteShader(_vertID);
		glDeleteShader(_fragID);
		std::printf("%s\n", &(errorLog[0]));
		error("Shader linking error M8");
	}

	glDetachShader(_programID, _vertID);
	glDetachShader(_programID, _fragID);
	glDeleteShader(_vertID);
	glDeleteShader(_fragID);
}

void Shader::addAttribute(const char* attrb) {
	glBindAttribLocation(_programID, _attributeCount++, attrb);
}

void Shader::useProgram() {
	glUseProgram(_programID);

	for (int i = 0; i < _attributeCount; i++) {
		glEnableVertexAttribArray(i);
	}
}

void Shader::unUseProgram() {
	glUseProgram(0);

	for (int i = 0; i < _attributeCount; i++) {
		glDisableVertexAttribArray(i);
	}
}

GLuint Shader::getUniformLocation(const char* dir) {
	GLint location = glGetUniformLocation(_programID,dir);
	if (location == GL_INVALID_INDEX)error("Hey moron, check your uniform variables!\nI couldn't find one of them!");
	return location;
}

void Shader::set1i(const char* name, int value) {
	glUniform1i(getUniformLocation(name), value);
}

void Shader::set1f(const char* name, float value) {
	glUniform1f(getUniformLocation(name),value);
}

void Shader::set2f(const char* name, float x,float y) {
	glUniform2f(getUniformLocation(name), x, y);
}

void Shader::set4f(const char* name, float r, float g,float b,float a) {
	glUniform4f(getUniformLocation(name), r, g, b, a);
}

void Shader::setMat4(const char* name,glm::mat4 mat) {
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}
