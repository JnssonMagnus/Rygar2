#pragma once
#include <GrowingArray.h>
#include <Vector2.h>
#include "sprite.h"

class MapChunk;
class Player;
class GameObject;

class Chain
{
public:
	enum class eState
	{
		eUnreleased,
		eFired,
		eStuck,
		eReturning
	};

				Chain();
	void		Init(const std::string_view aLinkSprite, const std::string_view aFireProjectileSprite, const float aMaxLength, 
		const float aInitSpeed, const int aReturnSpeed, GameObject* aEndObject = nullptr, const bool aStickToGround = true);
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

	bool							FirstLinkHitWall(Vector2f& finalPosition) const;
	bool							HasReachedMaxLength() const;

	CU::GrowingArray<Link>			myLinks;
	Sprite							myLinkSprite;
	Sprite							myHookSprite;
	GameObject*						myEndObject = nullptr;
	Vector2f						myParentPosition;
	Vector2f						myFireDirection;
	eState							myState;
	float							myHookInitSpeed;
	float							myHookSpeed;
	float							myHookAcc;
	float							myHookMaxLength = 60.f;

	float							myHookExtendFreq;
	float							myHookExtendTime;

	int								myReturnSpeed = 1;
	int								myLinkSize = 0;

	bool							myStickToGround = true;
};
