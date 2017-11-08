#pragma once
#include "Texture.h"
#include <vector>

class ImageIO
{
public:
	static Texture loadPNG(const char *path);//Loads and binds a texture
	static std::vector<unsigned char> loadPNGRaw(const char *path, unsigned long &width, unsigned long &height);//Loads a file with PicoPNG
	static void bindTexture(Texture &texture, const std::vector<unsigned char> &data);//Registers a texture to OpenGL
};
