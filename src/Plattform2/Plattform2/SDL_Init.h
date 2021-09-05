#pragma once

struct SDL_Window;
struct SDL_Surface;
struct SDL_Renderer;

namespace SDL
{
	struct SDL_Pointers
	{
		SDL_Window* myWindow = nullptr;
		SDL_Surface* myScreenSurface = nullptr;
		SDL_Renderer* myRenderer = nullptr;
	};

	SDL_Pointers Init(const int aScreenWidth, const int aScreenHeight);

}