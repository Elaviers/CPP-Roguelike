#pragma once
#include "Vector2.h"

struct EntityData {
	unsigned char ID;
	unsigned char *data;
	Vector2 position;
};

bool operator==(const EntityData& a, const EntityData& b);
bool operator<(const EntityData& a, const EntityData& b);
