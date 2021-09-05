#pragma once
#include "StateStatus.h"
#include <CommonMacros.h>

class StateStackProxy;
class EntitySystem;

class DllAPI State
{
public:
							State(StateStackProxy& aStateStackProxy, const bool aLetThroughRender = false);
	virtual					~State();

	virtual	eStateStatus	Update(const float aDeltaTime) = 0;
	virtual void			InitState();
	virtual void			EndState();
	virtual void			Render(const float aDeltaTime);
	virtual void			RegainFocus();
	bool					LetThroughRender() const;

protected:
	StateStackProxy&		myStateStackProxy;
	bool					myLetThroughRendering;


};

