#pragma once

#include "ComponentManager.h"

#include <vector>

class System
{
public:
	System(ComponentManager* cm) 
		: componentManager(cm) {}
		
	ComponentManager* componentManager;
};

