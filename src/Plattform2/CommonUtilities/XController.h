#pragma once
#include <Windows.h>
#include <Xinput.h>

namespace Input
{
	class XController
	{
	public:

	private:
		int				myPlayerNumber;
		XINPUT_STATE	myControllerState;
	};
}