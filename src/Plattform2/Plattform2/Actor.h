#pragma once
#include "GameObject.h"
#include "Animation.h"
#include <memory>

class AnimationController;

class Actor : public GameObject
{
public:
	virtual					~Actor();

	template<class AnimationControllerType, class ...ControllerTypeArgs>
	void					Init(GameObjectType& aGameObjectType, ControllerTypeArgs&... aControllerArgs);
	virtual void			Update(const float aDeltaTime) override;
	virtual void			Draw() override;
	virtual void			Damage(const int aDamage, const Vector2f& aContactPoint);
	virtual void			Stagger();
	virtual void			CollidedWithMap(const MapCollisionData& aMapCollisonData) override;
	bool					IsStaggered() const;


protected:
	AnimationController*	myAnimationController = nullptr;
	AnimationSet			myAnimationSet;

	int						myBloodHitAmount = 10;
	
	struct
	{
							float myStaggeredTime = 0.f;
							float myDamageOverLastFiveSeconds = 0.f;
							float myTimeToBeStaggared = 1.f;
							float myDamageToBeStaggered = 60.f;
	}						myStaggeredData;

private:
};

template<class AnimationControllerType, class ...ControllerTypeArgs>
void Actor::Init(GameObjectType& aGameObjectType, ControllerTypeArgs&... aControllerArgs)
{
	myProperties.SetValue(ePropertyValues::eFacingRight, true);
	myProperties.SetValue(ePropertyValues::eIsAttacking, false);
	GameObject::Init(aGameObjectType);
	myAnimationController = new AnimationControllerType(aControllerArgs...);
}