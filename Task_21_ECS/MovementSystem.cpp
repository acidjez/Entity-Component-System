#include "MovementSystem.h"

MovementSystem::MovementSystem(ComponentManager* cm)
	: System(cm)
{

}

void MovementSystem::Update()
{
	if (sprites.size() != componentManager->NumOfComponentType<SpriteComponent>())
	{
		sprites = componentManager->GetAllComponentsOfType<SpriteComponent>();
		std::cout << "Movement system updating sprites" << std::endl;
	}

	if (velocities.size() != componentManager->NumOfComponentType<VelocityComponent>())
	{
		velocities = componentManager->GetAllComponentsOfType<VelocityComponent>();
		std::cout << "Movement system updating velocities" << std::endl;
	}

	if (sprites.size() == 0)
	{
		std::cout << "No sprites to move" << std::endl;
		return;
	}

	if (velocities.size() == 0)
	{
		std::cout << "No velocities to move sprites with" << std::endl;
		return;
	}


	for (auto& s : sprites)
	{
		for (auto& v : velocities)
		{
			if (s->entity == v->entity)
			{
				s->dest.x += v->x;
				s->dest.y += v->y;
				break;
			}
		}
	}
}