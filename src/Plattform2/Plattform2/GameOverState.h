#pragma once
#include "State.h"

class GameOverState : public State
{
public:
					using State::State;
	eStateStatus	Update(const float aDeltaTime) override;
	void			Render(const float aDeltaTime) override;
	void			InitState() override;

private:

};

