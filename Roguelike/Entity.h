#pragma once
#include <Engine/GameObject.h>
#include <Engine/Vector2.h>

struct EntityData {
	unsigned char ID;
	unsigned char *data;
	Vector2 position;
};

bool operator<(const EntityData& a, const EntityData& b);

class Entity : public GameObject
{
public:
	unsigned char ID;

	virtual void loadData(const char* raw) {};
	virtual unsigned char* getData() const { return NULL; };

	Entity(unsigned char ID, Vector2f pos);
	virtual ~Entity();
};

