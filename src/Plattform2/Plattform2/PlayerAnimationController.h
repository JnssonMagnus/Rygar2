#pragma once
#include "AnimationController.h"

class PlayerAnimationController : public AnimationController
{
public:
	using			AnimationController::AnimationController;
	void			Update() override;
private:
	void			ChoseInAirAnimation();
	void			ChoseOnGroundAnimation();
};
