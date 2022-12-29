#pragma once

#include "SDL_Init.h"
#include "RenderCommands.h"
#include <StaticArray.h>
#include <Stack.h>
#include <PostMaster/Observer.h>

struct TextureResource;
struct FontResource;
struct SDL_Texture;

class Camera;
struct Particle;
struct SDL_Rect;

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
	void													AddDebugLine(const Vector2<int>& aStart, const Vector2<int>& aEnd);
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
	void													DrawDebugLines();
	void													CopyCurrentCameraData();
	
	void													WorldPosToCameraSpace(SDL_Rect& aWorldPos, const bool aUseZoom);

	SDL::SDL_Pointers										mySDL_Pointers;

	SDL_Texture*											myRenderTarget = nullptr;

	CU::StaticArray<CU::GrowingArray<RenderCommand>, 2>		myRenderCommands;
	CU::StaticArray<CU::GrowingArray<RenderCommand>, 2>		myGUIRenderCommands;
	CU::StaticArray<CU::GrowingArray<TextRenderCommand>, 2>	myTextRenderCommands;
	CU::StaticArray<CU::GrowingArray<PSRenderCommand>, 2>	myPSRenderCommands;
	CU::StaticArray<CU::GrowingArray<LineRenderCommand>, 2>	myDebugLines;

	struct {
		Vector2f											myPosition;
		float												myZoom;
	} myCopiedCameraData;

	CommonUtilities::Stack<Camera*>							myCameraStack;

};

