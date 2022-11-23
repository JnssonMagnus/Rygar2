#include "stdafx.h"
#include "State.h"


State::State(StateStackProxy& aStateStackProxy, const bool aLetThroughRender)
	: myStateStackProxy(aStateStackProxy)
{
	myLetThroughRendering = aLetThroughRender;
}

State::~State()
{
}

void State::InitState()
{
}

void State::EndState()
{
}

void State::Render(const float aDeltaTime)
{
}

void State::RegainFocus()
{
}

bool State::LetThroughRender() const
{
	return myLetThroughRendering;
}
