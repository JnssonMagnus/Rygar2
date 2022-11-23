#include "stdafx.h"
#include "Sprite.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL_image.h>
#include <assert.h>

Renderer* Sprite::ourRenderer = nullptr;

Sprite::Sprite()
{
	myPivot.myX = myPivot.myY = 0;
}

void Sprite::Draw(const Vector2f& aPosition, const float aAngle, const bool aNoZoom)
{
	ourRenderer->AddRenderCommand(aPosition, myTexture.GetResource()->mySize, myPivot, myTexture, aAngle, aNoZoom);
}

void Sprite::Draw(const Vector2f& aPosition, const Vector2<int>& aSrcPos, const Vector2<int>& aSrcSize, const float aAngle)
{
	ourRenderer->AddRenderCommand(aPosition, aSrcSize, aSrcPos, aSrcSize, myTexture);
}

void Sprite::Draw(const Vector2f& aPosition, const Vector2<int>& aDstSize, const Color& aColor, const unsigned char aAlpha)
{
	ourRenderer->AddRenderCommand(aPosition, aDstSize, { 0, 0 }, myTexture.GetResource()->mySize, myTexture, 0.f, aAlpha);
}

void Sprite::Draw(const Vector2f& aPosition, const Vector2<int>& aDstSize, const float aAngle)
{
	RenderCommand rc;
	rc.myAngle = aAngle;
	rc.myDstPos = aPosition;
	rc.myPivot = myPivot;
	rc.myDstSize = aDstSize;
	rc.myTexture = myTexture;
	rc.mySrcSize = myTexture.GetResource()->mySize;
	rc.mySrcPos = { 0, 0 };
	rc.myColor = { 255_uc, 255_uc, 255_uc};
	ourRenderer->AddRenderCommand(rc);
}

void Sprite::Init(const char* aFilename) 
{
	myTexture = ResourceManager::GetInstance()->GetTexture(aFilename);
}

void Sprite::SetPivot(const Vector2<int>& aPivot)
{
	myPivot = aPivot;
}

void Sprite::CenterPivot()
{
	myPivot.myX = static_cast<int>(GetSize().myX / 2.f);
	myPivot.myY = static_cast<int>(GetSize().myY / 2.f);
}

const Vector2<int>& Sprite::GetSize() const
{
	return myTexture.GetResource()->mySize;
}

void Sprite::SetRenderer(Renderer* aRenderer)
{
	ourRenderer = aRenderer;
}
