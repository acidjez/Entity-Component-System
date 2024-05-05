#pragma once
#include "ComponentManager.h"
#include <iostream>
#include <vector>
class EntityManager
{

public:
	EntityManager(ComponentManager& cm) 
		: componentManager(&cm)
	{};

	~EntityManager() {};

	uint32_t CreateEntity()  //
	{
		static uint32_t nextID = 0;
		uint32_t e = nextID++;
		entities.emplace_back(e);
		return e;
	}

	void DestroyEntity(uint32_t e)  //remove entity from list and destroy all components
	{
		for (auto it = entities.begin(); it != entities.end(); ++it)
		{
			if (*it == e)
			{
				componentManager->RemoveAllComponents(e);
				entities.erase(it);
				return;
			}
		}
		std::cout << "entity does not exist" << std::endl;
	}


	
	std::vector<uint32_t> entities;
	ComponentManager* componentManager;
};

