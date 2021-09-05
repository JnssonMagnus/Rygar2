#include "stdafx.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

ResourceManager* ResourceManager::ourInstance = nullptr;

ResourceManager::ResourceManager()
{
	mySDL_Renderer = nullptr;
}

void ResourceManager::Init(SDL_Renderer* aSDL_Renderer)
{
	DL_ASSERT(aSDL_Renderer != nullptr && "SDL_Renderer is nullptr!");
	mySDL_Renderer = aSDL_Renderer;
}

Texture ResourceManager::GetTexture(const char* aTextureName)
{
	auto it = myTextureIndexByName.find(aTextureName);
	if (it == myTextureIndexByName.end())
	{
		return LoadTexture(aTextureName);
	}
	else
	{
		return myTextures[it->second];
	}
}

Font ResourceManager::GetFont(const char* aFontName)
{
	auto it = myFontIndexByName.find(aFontName);
	if (it == myFontIndexByName.end())
	{
		return LoadFont(aFontName);
	}
	else
	{
		return myFonts[it->second];
	}

}

ResourceManager* ResourceManager::GetInstance()
{
	DL_ASSERT(ourInstance != nullptr && "ResourceManager isn't created yet!");
	return ourInstance;
}

void ResourceManager::Create()
{
	DL_ASSERT(ourInstance == nullptr && "ResourceManager is already created!");
	ourInstance = new ResourceManager();
}

void ResourceManager::Destroy()
{
	DL_ASSERT(ourInstance != nullptr && "ResourceManager is already destroyed!");
	SAFE_DELETE(ourInstance);
}

Texture ResourceManager::LoadTexture(const char* aTextureName)
{
	SDL_Surface* surface = IMG_Load(aTextureName);
	DL_ASSERT(surface != nullptr && "Failed to load image!");
	DL_ASSERT(mySDL_Renderer != nullptr && "ResourceManager isn't intiated!");
	SDL_Texture* sdl_texture = SDL_CreateTextureFromSurface(mySDL_Renderer, surface);
	SDL_FreeSurface(surface);
	int width = 0;
	int height = 0;
	SDL_QueryTexture(sdl_texture, NULL, NULL, &width, &height);

	TextureResource* newResource = new TextureResource{ sdl_texture, Vector2<int>(width, height) };
	Texture newTexture(newResource);
	myTextures.Add(newTexture);
	myTextureIndexByName[aTextureName] = myTextures.Size() - 1;

	std::cout << "Texture " << aTextureName << " loaded!" << std::endl;

	return newTexture;
}

Font ResourceManager::LoadFont(const char* aFontName)
{
	TTF_Font* font = TTF_OpenFont(aFontName, 16);
	if (font == nullptr)
	{
		DL_DEBUG("Font not found: %s", aFontName);
		DL_ASSERT(false && "Font not found!");
	}
	FontResource* newResource = new FontResource{ font };
	Font newFont(newResource);
	myFonts.Add(newFont);

	myFontIndexByName[aFontName] = myFonts.Size() - 1;
	std::cout << "Texture " << aFontName << " loaded!" << std::endl;

	return newFont;
}
