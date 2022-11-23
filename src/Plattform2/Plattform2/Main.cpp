#include "stdafx.h"
#include <Engine.h>
#include "GameState.h"
#include "Megaton.h"


int main(int argc, char* argv[])
{
	Megaton::Create();
	Engine engine;
	engine.Init();
	engine.AddState<GameState>();
	engine.MainLoop();

	return 0;
}