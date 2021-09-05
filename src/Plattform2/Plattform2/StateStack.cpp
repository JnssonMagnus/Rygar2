#include "stdafx.h"
#include "StateStack.h"
#include "State.h"
#include <assert.h>

StateStack::StateStack() : myStateStackProxy(*this)
{
	myMainStateIndex = -1;
	myStateIndex = -1;
	myNextAction = eStateStatus::eKeepState;
}


StateStack::~StateStack()
{
	myMainStateIndex = -1;
	myStateIndex = -1;
}

void StateStack::PopState()
{
	assert(myStates.Size() != 0 && "Can't pop empty stack!");

	myStates[myMainStateIndex][myStateIndex]->EndState();

	delete myStates[myMainStateIndex][myStateIndex];

	myStates[myMainStateIndex].RemoveCyclicAtIndex(myStateIndex);
	--myStateIndex;

	if (myStates[myMainStateIndex].Size() > 0)
	{
		myStates[myMainStateIndex][myStateIndex]->RegainFocus();
	}
	else
	{
		myStates.RemoveCyclicAtIndex(myMainStateIndex);

		--myMainStateIndex;
		if (myMainStateIndex >= 0)
		{
			myStateIndex = myStates[myMainStateIndex].Size() - 1;
		}
		else
		{
			myStateIndex = -1;
		}
	}
}

void StateStack::PopMainState()
{
	while (myMainStateIndex >= 0 && myStates[myMainStateIndex].Size() > 0)
	{
		PopState();
	}
}

void StateStack::PushState(State* aGameState)
{
	assert(myStates.Size() != 0 && "Can't push game state. No main game state present!");
	myStates[myMainStateIndex].Add(aGameState);
	aGameState->InitState();
	
	myStateIndex = myStates[myMainStateIndex].Size() - 1;
}

void StateStack::PushMainState(State* aGameState)
{
	myStates.Add(CU::GrowingArray<State*>());
	myMainStateIndex = myStates.Size() - 1;
	PushState(aGameState);
}

void StateStack::UpdateCurrentState(const float aDeltaTime)
{
	assert(myStates.Size() > 0 && "StateStack has no states!");
	myNextAction = myStates[myMainStateIndex][myStateIndex]->Update(aDeltaTime);
}

bool StateStack::RemoveExitedStates()
{
	switch (myNextAction)
	{
	case eStateStatus::ePopState:
		PopState();
		break;
	case eStateStatus::ePopMainState:
		PopMainState();
		break;
	case eStateStatus::eKeepState:
		break;
	}

	return (myStates.Size() > 0);
}

void StateStack::RenderCurrentState(const float aDeltaTime)
{
	assert(myStates.Size() > 0 && "No gamestate is present!");
	RenderStateAtIndex(myStateIndex, aDeltaTime);
}

void StateStack::RenderStateAtIndex(int aStateIndex, const float aDeltaTime)
{
	if (aStateIndex < 0)
	{
		return;
	}

	if (myStates[myMainStateIndex][aStateIndex]->LetThroughRender() == true)
	{
		RenderStateAtIndex(aStateIndex - 1, aDeltaTime);
	}

	myStates[myMainStateIndex][aStateIndex]->Render(aDeltaTime);
}

void StateStack::Clear()
{
	while (myStates.Size() > 0 && myMainStateIndex != -1)
	{
		PopMainState();
	}
}

StateStackProxy& StateStack::GetProxyObject()
{
	return myStateStackProxy;
}
