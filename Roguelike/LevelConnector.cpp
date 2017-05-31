#include "LevelConnector.h"



LevelConnector::LevelConnector()
{
}


LevelConnector::~LevelConnector()
{
}

void LevelConnector::GetProperties(PropertySet& properties) const {
	properties.setChar("ConnectionID",connectionID);
	properties.setChar("Direction",direction);
}

void LevelConnector::SetProperties(const PropertySet& properties) {
	connectionID = properties.getChar("ConnectionID");
	direction = properties.getChar("Direction");
}
