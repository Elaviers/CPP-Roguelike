#pragma once
#include "Vector2.h"

struct EntityData {
	unsigned char ID;
	unsigned char *data;
	signed char x;
	signed char y;
};

const bool operator==(const EntityData& a, const EntityData& b);
