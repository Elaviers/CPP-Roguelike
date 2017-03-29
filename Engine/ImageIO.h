#pragma once
#include <string>
#include <vector>
#include "Texture.h"
class ImageIO
{
public:
	static Texture loadPNG(const std::string path);//Loads and binds a texture
	static std::vector<unsigned char> loadPNGRaw(const std::string &path, unsigned long &width, unsigned long &height);//Loads a file with PicoPNG
	static void bindTexture(Texture &texture, const std::vector<unsigned char> &data);//Registers a texture to OpenGL
};