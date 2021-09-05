#include "stdafx.h"
#include "Engine.h"


int main(int argc, char* argv[])
{
	Engine engine;
	engine.Init();
	engine.MainLoop();

	return 0;
}