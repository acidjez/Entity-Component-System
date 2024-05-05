#pragma once

#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"


class ECS
{
public:
	ECS()
	{
		componentManager = new ComponentManager();
		entityManager = new EntityManager(*componentManager);	
		systemManager = new SystemManager(*componentManager);
	}
	~ECS() {}

	ComponentManager* componentManager;
	EntityManager* entityManager;
	SystemManager* systemManager;
};

