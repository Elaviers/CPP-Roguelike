#include "Background.h"



Background::Background()
{
}


Background::~Background()
{
}

void Background::init(std::string path) {
	_sprite.init(0,0,32,32,false,path);
	_sprite.UVGridDivisions = 8;
	_sprite.swapUVs(0);
}

void Background::render() {
	_sprite.render();
}