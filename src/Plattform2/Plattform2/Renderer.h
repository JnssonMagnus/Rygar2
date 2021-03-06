#pragma once

#include "SDL_Init.h"
#include "typedefs.h"
#include <StaticArray.h>
#include <Vector2.h>
#include <Stack.h>
#include <PostMaster/Observer.h>

struct TextureResource;
struct FontResource;

class Camera;
struct Particle;

struct TextRenderCommand
{
	Vector3<unsigned char>	myColor;
	Vector2<int>			myPosition;
	std::string				myText;
	Font					myFont;
};

struct PSRenderCommand
{
	CU::GrowingArray<Particle>* myParticles;
	Texture						myTexture;
	int							myBlendMode = 1;
};


struct RenderCommand
{
	enum eRenderOptions : unsigned char
	{
		eFlipped = 1,
		eNoZoom = 1 << 1
	};

	Vector3<unsigned char>	myColor;
	Vector2f				myDstPos;
	Vector2<int>			myDstSize;
	Vector2<int>			mySrcPos;
	Vector2<int>			mySrcSize;
	Vector2<int>			myPivot;
	Texture					myTexture;
	float					myAngle;
	unsigned char			myAlpha = 255_uc;
	unsigned char			myOptions = 0;
};

class Renderer : public Observer
{
public:
															Renderer();
															~Renderer();
	void													Init();
	void													AddTextRenderCommand(const Vector2<int>& aPosition, const std::string& aText, Font aFont, const Color& aColor);

	void													AddGUIRenderCommand(const Vector2f& aDstPos, const Vector2<int>& aDstSize, const Vector2<int>& aSrcPos, const Vector2<int>& aSrcSize, const Color& aColor, Texture aTexture);
	void													AddPSRenderCommand(const PSRenderCommand& aPSRenderCommand);

	void													AddRenderCommand(RenderCommand& aRenderCommand);
	void													AddRenderCommand(const Vector2f& aDstPos, const Vector2<int>& aDstSize, const Vector2<int>& aPivot, Texture aTexture, const float aAngle, const bool aNoZoom = false);
	void													AddRenderCommand(const Vector2f& aDstPos, const Vector2<int>& aDstSize, const Vector2<int>& aSrcPos, const Vector2<int>& aSrcSize, Texture aTexture, const float aAngle = 0.f, const unsigned char aAlpha = 255_uc);
	void													Draw(); 
	void													SwapRenderBuffer();
	void													UpdateCamera();
	void													RecieveMessage(const Message& aMessage) override;
	SDL_Renderer*											GetSDL_Renderer();

	void													PushCamera(Camera* aCamera);
	void													PopCamera();

private:
	void													DrawSprites();
	void													DrawText();
	void													DrawGUISprites();
	void													DrawParticleSystems();

	SDL::SDL_Pointers										mySDL_Pointers;

	CU::StaticArray<CU::GrowingArray<RenderCommand>, 2>		myRenderCommands;
	CU::StaticArray<CU::GrowingArray<RenderCommand>, 2>		myGUIRenderCommands;
	CU::StaticArray<CU::GrowingArray<TextRenderCommand>, 2>	myTextRenderCommands;
	CU::StaticArray<CU::GrowingArray<PSRenderCommand>, 2>	myPSRenderCommands;

	Vector2f												myBufferedCameraPosition;
	CommonUtilities::Stack<Camera*>							myCameraStack;	
};

