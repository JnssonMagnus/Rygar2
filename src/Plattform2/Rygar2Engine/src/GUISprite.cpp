#include "stdafx.h"
#include "GUISprite.h"
#include "Renderer.h"

void GUISprite::Draw(const Vector2f& aPosition, const Vector2<int>& aSrcPos, const Vector2<int>& aSrcSize, const float aRotation)
{
	Sprite::ourRenderer->AddGUIRenderCommand(aPosition, aSrcSize, aSrcPos, aSrcSize, { 255_uc, 255_uc, 255_uc }, myTexture);
}

void GUISprite::Draw(const Vector2f& aPosition, const Vector2<int>& aDstSize, const Color& aColor, const unsigned char aAlpha)
{
	Sprite::ourRenderer->AddGUIRenderCommand(aPosition, aDstSize, { 0, 0 }, myTexture.GetResource()->mySize, aColor, myTexture);
}