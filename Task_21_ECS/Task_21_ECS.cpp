//#define SDL_MAIN_HANDLED

#include <iostream>

#include "Components.h"

#include "ECS.h"
#include <SDL.h>
#include <SDL_image.h>

int main(int argc, char** argv)
{
	ECS ECS;
	std::cout << "Adding 3 player entities... \n" << std::endl;
	uint32_t player1 = ECS.entityManager->CreateEntity();
	uint32_t player2 = ECS.entityManager->CreateEntity();
	uint32_t player3 = ECS.entityManager->CreateEntity();

	//add 3 entities to entity manager
	for (auto &e : ECS.entityManager->entities)
	{
		std::cout << "Player: " << e << std::endl;
	}
	
	std::cout << "\nAdding components to entities... \n" << std::endl;
	//add components to created entitys
	ECS.componentManager->AddComponent<SpriteComponent>(player1, 2, 2);
	ECS.componentManager->AddComponent<VelocityComponent>(player1, 1, 1);
	ECS.componentManager->AddComponent<CollisionComponent>(player1);
							
	ECS.componentManager->AddComponent<SpriteComponent>(player2, 400, 100);
	ECS.componentManager->AddComponent<VelocityComponent>(player2, 1, 2);
	ECS.componentManager->AddComponent<CollisionComponent>(player2);

	ECS.componentManager->AddComponent<SpriteComponent>(player3, 400, 100);
	
	std::cout << "Testing sprite components were added to all 3 entities... \n" << std::endl;
	//test it adding component was successful
	for (auto& p : ECS.entityManager->entities)
	{
		if (ECS.componentManager->hasComponent<SpriteComponent>(p))
		{
			std::cout << "p" << p+1 << " has sprite" << std::endl;
		}
		else
		{
			std::cout << "p" << p+1 << " does not have sprite" << std::endl;
		}
	}

	std::cout << "\nTesting numOfComponents map is reporting correctly... \n" << std::endl;

	std::cout << "There are " << ECS.componentManager->NumOfComponentType<SpriteComponent>() << " Sprite components in total\n" << std::endl;
	

	std::cout << "Deleting player 3 entity... \n" << std::endl;
	ECS.entityManager->DestroyEntity(player3);

	std::cout << "Testing entity and its components were deleted... \n" << std::endl;
	for (auto& p : ECS.entityManager->entities)
	{
		if (ECS.componentManager->hasComponent<SpriteComponent>(p))
		{
			std::cout << "p" << p + 1 << " has sprite" << std::endl;
		}
		else
		{
			std::cout << "p" << p + 1 << " does not have sprite" << std::endl;
		}
	}
	std::cout << "There are " << ECS.componentManager->NumOfComponentType<SpriteComponent>() << " Sprite components in total\n\n" << std::endl;



	//get pointer to sprite component
	auto p1sprite = ECS.componentManager->GetComponent<SpriteComponent>(player1);
	auto p2sprite = ECS.componentManager->GetComponent<SpriteComponent>(player2);
	//initalise sprite component
	p1sprite->surface = IMG_Load("assets/1.png");
	p1sprite->texture = SDL_CreateTextureFromSurface(ECS.systemManager->renderSystem->renderer, p1sprite->surface);
	p1sprite->Init();

	p2sprite->surface = IMG_Load("assets/1.png");
	p2sprite->texture = SDL_CreateTextureFromSurface(ECS.systemManager->renderSystem->renderer, p2sprite->surface);
	p2sprite->Init();


	while (true)
	{
		ECS.systemManager->Update();
		ECS.systemManager->Render();
	}

	return 0;
}