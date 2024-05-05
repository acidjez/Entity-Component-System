#pragma once

#include "System.h"

#include "SDL.h"
#include "SDL_image.h"

class RenderSystem : public System
{
public:
	RenderSystem(uint32_t SCREEN_WIDTH, uint32_t SCREEN_HEIGHT, ComponentManager* cm);
	

	~RenderSystem();


	void Render();

	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector <SpriteComponent*> sprites;
};
