#pragma once
#include "Vector2.h"
#include <array>

struct _XINPUT_STATE;
using XINPUT_STATE = _XINPUT_STATE;

namespace Input
{
	enum class eControllerButtons : unsigned short
	{
		XINPUT_GAMEPAD_DPAD_UP        =  0x0001,
		XINPUT_GAMEPAD_DPAD_DOWN      =  0x0002,
		XINPUT_GAMEPAD_DPAD_LEFT      =  0x0004,
		XINPUT_GAMEPAD_DPAD_RIGHT     =  0x0008,
		XINPUT_GAMEPAD_START          =  0x0010,
		XINPUT_GAMEPAD_BACK           =  0x0020,
		XINPUT_GAMEPAD_LEFT_THUMB     =  0x0040,
		XINPUT_GAMEPAD_RIGHT_THUMB    =  0x0080,
		XINPUT_GAMEPAD_LEFT_SHOULDER  =  0x0100,
		XINPUT_GAMEPAD_RIGHT_SHOULDER =  0x0200,
		XINPUT_GAMEPAD_A              =  0x1000,
		XINPUT_GAMEPAD_B              =  0x2000,
		XINPUT_GAMEPAD_X              =  0x4000,
		XINPUT_GAMEPAD_Y              =  0x8000
	};

	enum class ePlayer
	{
		eOne,
		eTwo,
		eThree,
		eFour
	};

	class XInputWrapper
	{
	public:
		void			Update();
		bool			ControllerIsConnected(const int aControllerIndex) const;

		Vector2f		GetLeftThumbStick(const int aControllerIndex) const;
		Vector2f		GetRightThumbStick(const int aControllerIndex) const;
		float			GetRTrigger2(const int aControllerIndex) const;
		float			GetLTrigger2(const int aControllerIndex) const;
		bool			GetButtonDown(const int aControllerIndex, const eControllerButtons aControllerBtn) const;
		void			SetVibration(const int aControllerIndex, const unsigned short aLeftSpeed,
							const unsigned short aRightSpeed) const;
		

	private:
		std::array<XINPUT_STATE*, 4>
						myState;
		float			myDeadZone = 0.1f;
	};
}
