#pragma once
#include <GrowingArray.h>
#include <Vector2.h>
#include "sprite.h"

class Map;
class Player;

class Hook
{
public:
	enum class eState
	{
		eUnreleased,
		eFired,
		eStuck,
		eReturning
	};

				Hook();
	void		Init();
	void		Fire(const Vector2f& aDirection);
	void		Draw();
	Vector2f	Update(const float aDeltaTime, const Vector2f& aParentPosition, const Vector2f& aParentVelocity);
	void		Extend();
	void		Shorten();
	eState		GetState() const;

private:

	struct Link
	{
		Vector2f myPosition;
		Vector2f myVelocity;
		float myRotation = 0.f;
	};

	CU::GrowingArray<Link>			myLinks;
	Sprite							myLinkSprite;
	Sprite							myHookSprite;
	Vector2f						myParentPosition;
	Vector2f						myFireDirection;
	Map*							myMap = nullptr;
	eState							myState;
	float							myHookInitSpeed;
	float							myHookSpeed;
	float							myHookAcc;

	float							myHookExtendFreq;
	float							myHookExtendTime;

	int								myLinkSize = 0;
};
