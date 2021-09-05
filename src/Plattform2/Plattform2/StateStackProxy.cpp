#include "stdafx.h"
#include "StateStackProxy.h"
#include "StateStack.h"

StateStackProxy::StateStackProxy(StateStack& aStateStack) : myStateStack(aStateStack)
{
}

StateStackProxy::~StateStackProxy()
{
}

void StateStackProxy::PushState(State* aGameState)
{
	myStateStack.PushState(aGameState);
}

void StateStackProxy::PushMainState(State* aGameState)
{
	myStateStack.PushMainState(aGameState);
}
