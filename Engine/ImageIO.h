#pragma once
#include <string>
#include <vector>
#include "Texture.h"
static class ImageIO
{
public:
	static Texture loadPNG(std::string path);
	static std::vector<unsigned char> loadPNGRaw(std::string path,unsigned long &width,unsigned long &height);
	static void bindTexture(Texture &texture, std::vector<unsigned char> data);
};