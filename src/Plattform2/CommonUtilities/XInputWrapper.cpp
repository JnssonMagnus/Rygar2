#include "stdafx.h"
#include "XInputWrapper.h"
#include <windows.h>
#include <Xinput.h>

namespace Input
{
	void XInputWrapper::Update()
	{
		ZeroMemory(&myState, sizeof(std::array<XINPUT_STATE*, 4>));
		DWORD result = XInputGetState(0, myState[0]);
	}

	bool XInputWrapper::ControllerIsConnected(const int aControllerIndex) const
	{
		assert(aControllerIndex >= 0 && aControllerIndex < XUSER_MAX_COUNT && "Invalid controller index!");
		DWORD dwResult;
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		
		dwResult = XInputGetState(aControllerIndex, &state);

		return (dwResult == ERROR_SUCCESS);
	}

	Vector2f XInputWrapper::GetLeftThumbStick(const int aControllerIndex) const
	{		
		return { static_cast<float>(myState[aControllerIndex]->Gamepad.sThumbLX / 32767.f), 
			static_cast<float>(myState[aControllerIndex]->Gamepad.sThumbLY / 32767.f) };
	}

	Vector2f XInputWrapper::GetRightThumbStick(const int aControllerIndex) const
	{
		return { static_cast<float>(myState[aControllerIndex]->Gamepad.sThumbRX / 32767.f), static_cast<float>(myState[aControllerIndex]->Gamepad.sThumbRY / 32767.f) };
	}

	float XInputWrapper::GetRTrigger2(const int aControllerIndex) const
	{
		return static_cast<float>(myState[aControllerIndex]->Gamepad.bRightTrigger / 255.f);
	}

	float XInputWrapper::GetLTrigger2(const int aControllerIndex) const
	{
		return static_cast<float>(myState[aControllerIndex]->Gamepad.bLeftTrigger / 255.f);
	}

	bool XInputWrapper::GetButtonDown(const int aControllerIndex, const eControllerButtons aControllerBtn) const
	{
		return static_cast<float>(myState[aControllerIndex]->Gamepad.wButtons & static_cast<WORD>(aControllerBtn));
	}

	void XInputWrapper::SetVibration(const int aControllerIndex, const unsigned short aLeftSpeed,
		const unsigned short aRightSpeed) const
	{
		XINPUT_VIBRATION vibration;
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		vibration.wLeftMotorSpeed = aLeftSpeed;
		vibration.wRightMotorSpeed = aRightSpeed;
		XInputSetState(aControllerIndex, &vibration);
	}
}