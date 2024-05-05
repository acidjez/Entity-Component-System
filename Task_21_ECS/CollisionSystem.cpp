#include "CollisionSystem.h"

CollisionSystem::CollisionSystem(ComponentManager* cm)
	: System(cm)
{

}


void CollisionSystem::Update()
{
	if (sprites.size() != componentManager->NumOfComponentType<SpriteComponent>()) //check if the number of sprites has changed
	{
		sprites = componentManager->GetAllComponentsOfType<SpriteComponent>();     //if it has, update the sprites pointer vector
		std::cout << "Collision system updating sprites" << std::endl;
	}

	static uint32_t i = 0;
	for (auto& s : sprites)
	{
		if (componentManager->hasComponent<CollisionComponent>(s->entity))  //check if the sprite has a collision component
		{
			componentManager->GetComponent<CollisionComponent>(s->entity)->isColliding = false;

			if (s->dest.x <= 0 || (s->dest.x + s->dest.w) >= 800)         //check if the sprite is colliding with the edge of the screen
			{
				componentManager->GetComponent<VelocityComponent>(s->entity)->x *= -1;
			}

			if (s->dest.y <= 1 || (s->dest.y + s->dest.h) >= 600)        //check if the sprite is colliding with the edge of the screen
			{
				componentManager->GetComponent<VelocityComponent>(s->entity)->y *= -1;
			}

			for (auto& otherS : sprites)
			{
				if (s->entity != otherS->entity)
				{
					if (SDL_HasIntersectionF(&s->dest, &otherS->dest))            //check if the sprite is colliding with another sprite
					{
						if (!(componentManager->GetComponent<CollisionComponent>(s->entity)->isColliding))
						{
							componentManager->GetComponent<VelocityComponent>(s->entity)->x *= -1;
							componentManager->GetComponent<VelocityComponent>(s->entity)->y *= -1;
							componentManager->GetComponent<CollisionComponent>(s->entity)->isColliding = true;
						}

						std::cout << "Collision detected" << i << std::endl;
						i++;
					}
				}
			}
		}
	}
}