#include "stdafx.h"
#include "ParallaxLayer.h"

void ParallaxLayer::Init(const char* aImageFilename, const Vector2f& aMovePercent)
{
	mySprite.Init(aImageFilename);
	myMovePercent = aMovePercent;
}

void ParallaxLayer::Render(const Vector2f& aCameraPosition, const float aCameraZoom)
{
	Vector2f position = aCameraPosition * myMovePercent * -1.f * aCameraZoom;
	position.myX = static_cast<float>(static_cast<int>(position.myX) % SCREEN_WIDTH);
	position += aCameraPosition;

	position.myX -= mySprite.GetSize().myX / 2;
	position.myY -= mySprite.GetSize().myY / 2;
	mySprite.Draw(position, 0.f, true);
}
