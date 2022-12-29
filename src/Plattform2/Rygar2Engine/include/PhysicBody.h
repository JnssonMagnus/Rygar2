#pragma once
#include "PhysicStates.h"
#include <vector2.h>
#include <StaticArray.h>

class GameObject;

enum class ePhysicBodyOptions
{
	eEnable = 1,
	eRotateObject = 1 << 1,
	eGravity = 1 << 2,
	eKinetic = 1 << 3
};

enum class eCollisionTags
{
	ePlayer = 1,
	eBullet = 1 << 1,
	eEnemy = 1 << 2,
	ePickable = 1 << 3
};


class PhysicBody
{
public:
								
								PhysicBody();
								PhysicBody(const PhysicBody& aPhysicBody);
								~PhysicBody();
	PhysicBody&					operator=(const PhysicBody& aPhysicBody);
	void						Update();

	bool						Collides(const PhysicBody& aPhysicBody) const;
	bool						Collides(const Vector2f& aPoint) const;

	inline const Vector2f&		GetPosition() const;
	inline const Vector2f&		GetOldPosition() const;
	inline const Vector2f&		GetVelocity() const;
	inline const Vector2f&		GetForce() const;
	inline const Vector2f&		GetHalfSize() const;
	inline const Vector2f&		GetDirection() const;
	inline float				GetBounciness() const;
	inline float				GetMass() const;
	float						GetRotation() const;

	Vector2f					GetLeftBottom() const;
	Vector2f					GetRightBottom() const;
	Vector2f					GetRightTop() const;
	Vector2f					GetLeftTop() const;
	Vector2f					GetMiddleBottom() const;
	Vector2f					GetMiddleTop() const;

	void						TranslatePosition(const Vector2f& aOffset);
	void						SetFriction(const Vector2f& aAirFriction, const Vector2f& aGroundFriction);
	void						SetPosition(const Vector2f& aPosition);
	void						SetStartPosition(const Vector2f& aPosition);
	void						SetForce(const Vector2f& aForce);
	void						SetVelocity(const Vector2f& aVelocity);
	void						SetHalfSize(const Vector2f& aHalfSize);
	void						SetBounciness(const float aBounciness);
	void						SetMass(const float aWeight);
	void						SetCollisionTags(const char someCollisionTags);
	void						ChangeDirection();

	void						Release();
	void						AddForce(const Vector2f& aForce);

	enum class eLocator
	{
		eTop,
		eBottom,
		eLeft,
		eRight
	};

	bool						HasCollisionTag(const eCollisionTags aCollisionTag) const;

	void						AddPhysicState(const ePhysicStates aPhysicState, const eLocator aLocator);
	bool						HasPhysicState(const ePhysicStates aPhysicState, const eLocator aLocator) const;
	void						ResetPhysicState();

	bool						GetOption(const ePhysicBodyOptions) const;

	void						SetEnabled(const bool aFlag);
	void						SetGravity(const bool aIsEnabled);
	void						SetIsKinetic(const bool aIsKinetic);
	bool						IsEnabled() const;
	void						SetRotation(const bool aRotateWithSpeed);

	GameObject*					GetParent() const;
	void						SetParent(GameObject* aParent);
	
private:
	void						SetOption(const ePhysicBodyOptions aOption, const bool aValue);
	Vector2f					myPosition;
	Vector2f					myOldPosition;
	Vector2f					myVelocity;
	Vector2f					myForce;
	Vector2f					myHalfSize;
	Vector2f					myAirFriction;
	Vector2f					myGroundFriction;
	Vector2f					myDirection;
	Vector2f					myTranslationToAdd;
	CU::StaticArray<char, 4>	myPhysicStates;
	GameObject*					myGameObject;
	float						myBounciness;
	float						myMass;
	char						myOptions;
	char						myTags;
};


inline const Vector2f& PhysicBody::GetPosition() const
{
	return myPosition;
}

inline const Vector2f& PhysicBody::GetOldPosition() const
{
	return myOldPosition;
}

inline const Vector2f& PhysicBody::GetVelocity() const
{
	return myVelocity;
}

inline const Vector2f& PhysicBody::GetForce() const
{
	return myForce;
}

inline const Vector2f& PhysicBody::GetHalfSize() const
{
	return myHalfSize;
}

inline const Vector2f& PhysicBody::GetDirection() const
{
	return myDirection;
}

inline float PhysicBody::GetBounciness() const
{
	return myBounciness;
}

inline float PhysicBody::GetMass() const
{
	return myMass;
}

inline float PhysicBody::GetRotation() const
{
	float rot = (myPosition.myX / (myHalfSize.myX * static_cast<float>(PI)) * static_cast<float>(PI) * 1.5f);	
	return rot * static_cast<int>(GetOption(ePhysicBodyOptions::eRotateObject));
}

inline Vector2f PhysicBody::GetLeftBottom() const
{
	return myPosition + Vector2f(-myHalfSize.myX, myHalfSize.myY);
}

inline Vector2f PhysicBody::GetRightBottom() const
{
	return myPosition + myHalfSize;
}

inline Vector2f PhysicBody::GetRightTop() const
{
	return myPosition + Vector2f(myHalfSize.myX, -myHalfSize.myY);
}

inline Vector2f PhysicBody::GetLeftTop() const
{
	return myPosition - myHalfSize;
}

inline Vector2f PhysicBody::GetMiddleBottom() const
{
	return myPosition + Vector2f(0, myHalfSize.myY + 1);
}

inline Vector2f PhysicBody::GetMiddleTop() const
{
	return myPosition - Vector2f(0, myHalfSize.myY);
}

inline bool PhysicBody::IsEnabled() const
{
	return GetOption(ePhysicBodyOptions::eEnable);
}

inline GameObject* PhysicBody::GetParent() const
{
	return myGameObject;
}

inline void PhysicBody::SetParent(GameObject* aParent)
{
	myGameObject = aParent;
}
