#pragma once
#include "Vector2.h"

struct EntityData {
	unsigned char ID;
	unsigned char *data;
	Vector2 position;
};

const bool operator==(const EntityData& a, const EntityData& b);
