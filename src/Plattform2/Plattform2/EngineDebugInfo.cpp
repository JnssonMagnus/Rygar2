#include "stdafx.h"
#include "EngineDebugInfo.h"

EngineDebugInfo::EngineDebugInfo()
{
}

void EngineDebugInfo::Init()
{
	myFPS_Text.Init("data/fonts/corbel.ttf");
	myFPS_Text.SetPosition({ SCREEN_WIDTH - 80, 5 });
	SetFPS(0);
}

void EngineDebugInfo::SetFPS(const int aFPS)
{
	std::stringstream ss;
	ss << "FPS " << aFPS;
	myFPS_Text.SetText(ss.str().c_str());
}

void EngineDebugInfo::Draw()
{
	myFPS_Text.Draw();
}
