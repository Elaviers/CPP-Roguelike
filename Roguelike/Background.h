#pragma once
#include <string>
#include <Engine/Sprite.h>
#include <Engine/SpriteBatch.h>

class Background
{
private:
	Sprite _sprite;
	SpriteBatch _batch;
public:
	Background();
	~Background();

	void init(std::string texture);
	void render();
};

