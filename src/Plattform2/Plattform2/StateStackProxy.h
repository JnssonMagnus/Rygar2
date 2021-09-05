#pragma once

class StateStack;
class State;

class StateStackProxy
{
public:
					StateStackProxy(StateStack& aStateStack);
					~StateStackProxy();
	void			PushState(State* aGameState);
	void			PushMainState(State* aGameState);

private:
	StateStack&		myStateStack;
};

