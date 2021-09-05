#pragma once
#include "SharedResource.h"
#include "Texture.h"
#include "Font.h"
#include <GrowingArray.h>
#include <unordered_map>

struct SDL_Renderer;

class ResourceManager
{
public:
											ResourceManager();
	void									Init(SDL_Renderer* aSDL_Renderer);
	Texture									GetTexture(const char* aTextureName);
	Font									GetFont(const char* aFontName);
	static ResourceManager*					GetInstance();
	static void								Create();
	static void								Destroy();

private:
	Texture									LoadTexture(const char* aTextureName);
	Font									LoadFont(const char* aFontName);
	CU::GrowingArray<Texture>				myTextures;
	CU::GrowingArray<Font>					myFonts;
	std::unordered_map<std::string, int>	myTextureIndexByName;
	std::unordered_map<std::string, int>	myFontIndexByName;

	SDL_Renderer*							mySDL_Renderer;

	static ResourceManager*					ourInstance;
};

