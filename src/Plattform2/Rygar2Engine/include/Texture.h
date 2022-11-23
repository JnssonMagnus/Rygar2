#pragma once
#include "SharedResource.h"
#include <Vector2.h>

struct SDL_Texture;

struct TextureResource
{
	SDL_Texture*	myTexture;
	Vector2<int>	mySize;
};

typedef SharedResource<TextureResource> Texture;
