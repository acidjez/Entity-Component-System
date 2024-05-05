#pragma once
#include "System.h"


class MovementSystem : public System
{
public:

	MovementSystem(ComponentManager* cm);

	void Update();

private:
	std::vector<SpriteComponent*> sprites;
	std::vector<VelocityComponent*> velocities;
};
