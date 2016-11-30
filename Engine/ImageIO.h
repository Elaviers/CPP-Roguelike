#pragma once
#include <string>
#include <vector>
#include "Texture.h"
class ImageIO
{
public:
	static Texture loadPNG(std::string path);//Loads and binds a texture
	static std::vector<unsigned char> loadPNGRaw(std::string path,unsigned long &width,unsigned long &height);//Loads a file with PicoPNG
	static void bindTexture(Texture &texture, std::vector<unsigned char> data);//Registers a texture to OpenGL
};