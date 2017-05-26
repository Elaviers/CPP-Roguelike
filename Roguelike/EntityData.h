#pragma once
#include "Types.h"

struct EntityData {
	unsigned char ID;
	signed char x;
	signed char y;
	unsigned char *data;
};

const bool operator==(const EntityData& a, const EntityData& b);
