#include "RenderSystem.h"

RenderSystem::RenderSystem(uint32_t SCREEN_WIDTH, uint32_t SCREEN_HEIGHT, ComponentManager* cm)
	: System(cm)
{
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("RenderSystem", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

}
RenderSystem::~RenderSystem()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}


void RenderSystem::Render()
{
	if (sprites.size() != componentManager->NumOfComponentType<SpriteComponent>())			//check if the number of sprites has changed
	{
		sprites = componentManager->GetAllComponentsOfType<SpriteComponent>();				//if it has, update the sprites pointer vector
		std::cout << "Render system updating sprites" << std::endl;
	}
	if (sprites.size() == 0)
	{
		std::cout << "No sprites to render" << std::endl;
		return;
	}
	SDL_RenderClear(renderer);
	for (auto& sprite : sprites)
	{
		if (sprite->surface)
		{		
			SDL_RenderCopyF(renderer, sprite->texture, &sprite->rect, &sprite->dest);
			std::cout << sprite->entity << std::endl;
			//std::cout << "Rendered" << std::endl;
		}
	}
	SDL_RenderPresent(renderer);
}