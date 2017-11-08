#pragma once
#include <Engine/Entity.h>

class E_LevelConnector : public Entity {
public:
	E_LevelConnector();
	~E_LevelConnector();

	unsigned char connectionID;
	unsigned char direction;
	
	virtual void GetProperties(PropertySet&) const;
	virtual void SetProperties(const PropertySet&);
};
