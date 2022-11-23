#pragma once
#include "Text.h"
class EngineDebugInfo
{
public:
			EngineDebugInfo();
	void	Init();
	void	SetFPS(const int aFPS);
	void	Draw();

private:
	Text	myFPS_Text;
};

