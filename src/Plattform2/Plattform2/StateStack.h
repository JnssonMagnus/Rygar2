#pragma once
#include "StateStatus.h"
#include "StateStackProxy.h"
#include <GrowingArray.h>

class State;

class StateStack
{
public:
							StateStack();
							~StateStack();
	void					PushState(State* aGameState);
	void					PushMainState(State* aGameState);
	void					UpdateCurrentState(const float aDeltaTime);
	void					RenderCurrentState(const float aDeltaTime);
	bool					RemoveExitedStates();
	void					Clear();
	StateStackProxy&		GetProxyObject();

private:
	CU::GrowingArray<CU::GrowingArray<State*>>
							myStates;
	void					PopState();
	void					PopMainState();
	void					RenderStateAtIndex(int aStateIndex, const float aDeltaTime);
	int						myMainStateIndex;
	int						myStateIndex;
	eStateStatus			myNextAction;
	StateStackProxy			myStateStackProxy;
};

