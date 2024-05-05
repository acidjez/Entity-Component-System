#pragma once

#include "System.h"
#include "ComponentManager.h"
#include "RenderSystem.h"
#include "MovementSystem.h"
#include "CollisionSystem.h"

class SystemManager
{
public:

	SystemManager(ComponentManager& cm) 
	{
		renderSystem = new RenderSystem(800, 600, &cm);
		movementSystem = new MovementSystem(&cm);
		collisionSystem = new CollisionSystem(&cm);
	}
	~SystemManager() {}


	void Update()
	{
		collisionSystem->Update();
		movementSystem->Update();
	}

	void Render()
	{
		renderSystem->Render();
	}

	
	RenderSystem* renderSystem;
	MovementSystem* movementSystem;
	CollisionSystem* collisionSystem;
};
