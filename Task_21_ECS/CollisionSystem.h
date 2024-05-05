#pragma once

#include "System.h"


class CollisionSystem : public System
{
public:
	CollisionSystem(ComponentManager* cm);
	
	void Update();

	std::vector<SpriteComponent*> sprites;

};