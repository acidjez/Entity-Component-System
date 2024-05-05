#pragma once

#include <SDL.h>

#include <iostream>


struct Component
{
	virtual ~Component() = default;
	uint32_t entity;
};

struct PositionComponent : public Component
{
	PositionComponent() = default;
	PositionComponent(float x, float y) 
		: x(x), y(y) {}

	float x {};
	float y {};
};

struct VelocityComponent : public Component
{
	VelocityComponent() = default;
	VelocityComponent(float x, float y)
		: x(x), y(y) {}

	float x{};
	float y{};
};

struct SpriteComponent : public Component {
	SpriteComponent() = default;
	SpriteComponent(float x, float y)
	{
		dest.x = x;
		dest.y = y;
		rect.x = 0;
		rect.y = 0;
	}

	void Init()
	{
		rect.h = surface->h;
		rect.w = surface->w;
		dest.h = surface->h;
		dest.w = surface->w;
	}

	SDL_Rect rect;
	SDL_FRect dest;
	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;
};

struct CollisionComponent : public Component {
	CollisionComponent() = default;
	bool isColliding = false;
};