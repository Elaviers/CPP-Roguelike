#include "ImageIO.h"

#include "ErrorHandling.h"
#include "IOManager.h"
#include "PicoPNG.h"

#include <Gl/glew.h>

Texture ImageIO::loadPNG(std::string path) {
	unsigned long width, height;
	Texture texture;

	std::vector<unsigned char> out = loadPNGRaw(path, width, height);

	texture.Width = width;
	texture.Height = height;

	bindTexture(texture, out);

	return texture;
}

std::vector<unsigned char> ImageIO::loadPNGRaw(const std::string& path, unsigned long &width, unsigned long &height) {
	Texture texture = {};
	std::vector<unsigned char> in;
	std::vector<unsigned char> out;

	if (!IOManager::readFileToBuffer(path, in))error("I couldn't load an image.");

	int s = decodePNG(out, width, height, &(in[0]), in.size());

	if (s != 0) error("Wow, that PNG was hard to decode. Error code " + std::to_string(s) + ".");

	return out;
}

void ImageIO::bindTexture(Texture &texture, const std::vector<unsigned char>& data) {
	glGenTextures(1, &texture.ID);

	glBindTexture(GL_TEXTURE_2D, texture.ID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.Width, texture.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(data[0]));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}
