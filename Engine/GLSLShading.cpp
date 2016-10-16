#include <fstream>
#include <string>
#include <vector>
#include "GLSLShading.h"
#include "ErrorHandling.h"


GLSLShading::GLSLShading() :_attributeCount(0),  _programID(0), _vertID(0), _fragID(0) {
}


GLSLShading::~GLSLShading() {
}

void GLSLShading::compileShaders(const char* frag, const char* vert) {
	_programID = glCreateProgram();

	_vertID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertID == 0)
		error("Vertex shader issues mang");
	_fragID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragID == 0)
		error("Fragment shader issues mang");

	loadShader(frag,_fragID);
	loadShader(vert, _vertID);
}

void GLSLShading::loadShader(const char* dir,GLuint ID) {
	std::ifstream ShaderFile(dir);
	if (ShaderFile.fail()) {
		perror(dir);
		error("Ey gaylord, I couldn't open a shader!\n");
	}

	std::string contents = "", line;

	while (std::getline(ShaderFile, line))
		contents += line + '\n';
	ShaderFile.close();

	const char* readcontents = contents.c_str();
	glShaderSource(ID, 1, &readcontents, nullptr);
	glCompileShader(ID);

	GLint success = 0;
	glGetShaderiv(ID, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) {
		GLint maxlength = 0;
		glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &maxlength);

		std::vector<GLchar> errorLog(maxlength);
		glGetShaderInfoLog(ID, maxlength, &maxlength, &errorLog[0]);

		glDeleteShader(ID);
		std::printf("%s\n", &(errorLog[0]));
		error("Shader compilation error M8");
	}

}

void GLSLShading::linkShaders() {
	glAttachShader(_programID, _vertID);
	glAttachShader(_programID, _fragID);

	glLinkProgram(_programID);

	GLint linkSuccess = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int*)&linkSuccess);

	if (linkSuccess == GL_FALSE) {
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

void GLSLShading::addAttribute(const char* attrb) {
	glBindAttribLocation(_programID, _attributeCount++, attrb);
}

void GLSLShading::useProgram() {
	glUseProgram(_programID);

	for (int i = 0; i < _attributeCount; i++) {
		glEnableVertexAttribArray(i);
	}
}

void GLSLShading::unUseProgram() {
	glUseProgram(0);

	for (int i = 0; i < _attributeCount; i++) {
		glDisableVertexAttribArray(i);
	}
}

GLuint GLSLShading::getUniformLocation(const char* dir) {
	GLint location = glGetUniformLocation(_programID,dir);
	if (location == GL_INVALID_INDEX)error("Hey moron, check your uniform variables!");
	return location;
}
