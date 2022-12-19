#include "stdafx.h"
#include "SDL_Init.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <assert.h>

namespace SDL
{
	void InitTTF()
	{
		if (TTF_Init() == -1) 
		{
			DL_DEBUG("Error!TTF_Init: %s\n", TTF_GetError());
			DL_ASSERT("Failed to init SDL_TTF (font stuff)");
		}
		DL_PRINT("TTF initiated!");
	}

	SDL_Pointers Init(const int aScreenWidth, const int aScreenHeight)
	{
		SDL_Window* window = nullptr;
		SDL_Surface* screenSurface = nullptr;
		SDL_Renderer* renderer = nullptr;

		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError();
		}
		else
		{
			window = SDL_CreateWindow("Plattformer2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, aScreenWidth, aScreenHeight, SDL_WINDOW_SHOWN);
			if (window == NULL)
			{
				std::cout << "Window could not be created! SDL_Error: " << SDL_GetError();
			}
			else
			{
				screenSurface = SDL_GetWindowSurface(window);	
			}
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
			assert(renderer != nullptr && "Couldn't create SDL renderer!");
		}

		InitTTF();
		DL_PRINT("SDL initiated!");
		return { window, screenSurface, renderer };
	}
}