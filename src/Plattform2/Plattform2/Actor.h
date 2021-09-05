#pragma once
#include "GameObject.h"
#include "AnimationController.h"
#include "Animation.h"

class Actor : public GameObject
{
public:
	virtual void		Init(GameObjectType& aGameObjectType) override;
	virtual void		Update(const float aDeltaTime) override;
	virtual void		Draw() override;
	virtual void		Damage(const int aDamage, const Vector2f& aContactPoint);


protected:
	AnimationController	myAnimationController;
	AnimationSet		myAnimationSet;

	int					myBloodHitAmount = 5;
	
	struct
	{
						float myStaggeredTime = 0.f;
						float myDamageOverLastFiveSeconds = 0.f;
						float myTimeToBeStaggared = 1.f;
						float myDamageToBeStaggered = 60.f;
	}					myStaggeredData;

private:
};

