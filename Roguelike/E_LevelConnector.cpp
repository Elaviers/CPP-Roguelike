#include "E_LevelConnector.h"

#include <Engine/PropertySet.h>


E_LevelConnector::E_LevelConnector()
{
}


E_LevelConnector::~E_LevelConnector()
{
}

void E_LevelConnector::GetProperties(PropertySet& properties) const {
	properties.setChar("ConnectionID",connectionID);
	properties.setChar("Direction",direction);
}

void E_LevelConnector::SetProperties(const PropertySet& properties) {
	connectionID = properties.getChar("ConnectionID");
	direction = properties.getChar("Direction");
}
