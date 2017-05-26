#pragma once
#include "Entity.h"

class LevelConnector : public Entity {
public:
	LevelConnector();
	~LevelConnector();

	ID(1)

	unsigned char connectionID;
	unsigned char direction;

	virtual unsigned char* getData() const override;
};
