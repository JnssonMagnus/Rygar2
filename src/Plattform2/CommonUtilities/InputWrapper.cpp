#include "stdafx.h"
#include "InputWrapper.h"
#include "CommonMacros.h"
#include "Debugger/DL_Debug.h"
#include <assert.h>

namespace Input
{
	InputWrapper* InputWrapper::myInstance = nullptr;

	InputWrapper::InputWrapper()
	{
		myIsInitialized = false;

		// Set all keys to unpressed by default. ZeroMemory is a macro that 
		ZeroMemory(&myPreviousKeyState, sizeof(BYTE) * 256);
		ZeroMemory(&myKeyState, sizeof(BYTE) * 256);
		ZeroMemory(&myMouseState, sizeof(myMouseState));

		myWindowWidth = 0;
		myWindowHeight = 0;

		myWindowsMouseCapture = false;

		SetMouseSpeed(1);
		SetMousePosition(0, 0);
	}


	InputWrapper::~InputWrapper()
	{
		// Objects deletes all their allocated resources and clean up 
		myDirectInputMouse->Unacquire();
		myDirectInputKeyboard->Unacquire();
		myDirectInputMouse->Release();
		myDirectInputKeyboard->Release();
		myDirectInput->Release();
	}

	InputWrapper* InputWrapper::GetInstance()
	{
		if (myInstance == nullptr)
		{
			myInstance = new InputWrapper();
		}

		return myInstance;
	}

	void InputWrapper::Destroy()
	{
		DL_ASSERT(myInstance != nullptr && "Can't destroy instance of InputWrapper, none created!");
		SAFE_DELETE(myInstance);
	}


	void InputWrapper::Init(HINSTANCE aHInstance, HWND aHWND, int aWindowWidth, int aWindowHeight)
	{
		assert(aHWND != 0 && "HWND is null!");
		HRESULT result;

		// Initialize Direct Input
		result = DirectInput8Create(aHInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, reinterpret_cast<void**>(&myDirectInput), nullptr);
		if (SUCCEEDED(result) == false)
		{
			DL_PRINT("Warning! Failed to init direct input!");
			std::cout << "Warning! Failed to init direct input!" << std::endl;
			return;
		}

		// Initialize keyboard and mouse
		result = myDirectInput->CreateDevice(GUID_SysKeyboard, &myDirectInputKeyboard, nullptr);
		assert(SUCCEEDED(result) && "Failed to initialize keyboard.");

		result = myDirectInput->CreateDevice(GUID_SysMouse, &myDirectInputMouse, nullptr);
		assert(SUCCEEDED(result) && "Failed to initialize mouse.");


		// Set type format that the devices should return
		myDirectInputKeyboard->SetDataFormat(&c_dfDIKeyboard);
		myDirectInputMouse->SetDataFormat(&c_dfDIMouse);


		// Set how this program will use and share the input with other applications
		result = myDirectInputKeyboard->SetCooperativeLevel(aHWND, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		if (SUCCEEDED(result) == false)
		{
			DL_PRINT("Warning! Failed to set cooperative level on keyboard!");
			std::cout << "Warning! Failed to set cooperative level on keyboard!" << std::endl;
			return;
		}

		result = myDirectInputMouse->SetCooperativeLevel(aHWND, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		assert(SUCCEEDED(result) && "Failed to set cooperative level on mouse.");

		myWindowWidth = aWindowWidth;
		myWindowHeight = aWindowHeight;

		myHWND = aHWND;

		myIsInitialized = true;
	}


	bool InputWrapper::GetKeyDown(unsigned char aKey) const
	{
		assert(aKey < 256 && "Unknown Key!");
		return IsPressed(myKeyState[aKey]) == true && IsPressed(myPreviousKeyState[aKey]) == false;
	}


	bool InputWrapper::GetKeyPressed(unsigned char aKey) const
	{
		assert(aKey < 256 && "Unknown Key!");
		return IsPressed(myKeyState[aKey]) == true;
	}


	bool InputWrapper::GetKeyReleased(unsigned char aKey) const
	{
		assert(aKey < 256 && "Unknown Key!");
		return IsPressed(myKeyState[aKey]) == false && IsPressed(myPreviousKeyState[aKey]) == true;
	}


	bool InputWrapper::GetMouseButtonDown(const eMouseButtons aMouseButton) const
	{
		return IsPressed(myMouseState.rgbButtons[static_cast<int>(aMouseButton)]) == true &&
			IsPressed(myPreviousMouseState.rgbButtons[static_cast<int>(aMouseButton)]) == false;
	}

	bool InputWrapper::GetMouseButtonPressed(const eMouseButtons aMouseButton) const
	{
		return IsPressed(myMouseState.rgbButtons[static_cast<int>(aMouseButton)]) == true;
	}


	bool InputWrapper::GetMouseButtonReleased(const eMouseButtons aMouseButton) const
	{
		return IsPressed(myMouseState.rgbButtons[static_cast<int>(aMouseButton)]) == false && 
			IsPressed(myPreviousMouseState.rgbButtons[static_cast<int>(aMouseButton)]) == true;
	}


	Position InputWrapper::GetMousePosition() const
	{
		return myMousePosition;
	}


	Position InputWrapper::GetMouseDeltaPosition() const
	{
		Position position;
		position.myX = myMouseState.lX;
		position.myY = myMouseState.lY;
		return position;
	}

	Position InputWrapper::GetMouseDeltaPositionInPixels() const
	{
		Position position;
		position.myX = myMousePosition.myX - myOldMousePosition.myX;
		position.myY = myMousePosition.myY - myOldMousePosition.myY;
		return position;
	}


	LONG InputWrapper::GetMouseScroll() const
	{
		return myMouseState.lZ;
	}


	void InputWrapper::UpdateMousePosition()
	{
		myOldMousePosition = myMousePosition;
		myMousePosition.myX += static_cast<LONG>(myMouseState.lX * myMouseSpeed);
		myMousePosition.myY += static_cast<LONG>(myMouseState.lY * myMouseSpeed);

		myMousePosition.myX = RANGE(myMousePosition.myX, 1, myWindowWidth);
		myMousePosition.myY = RANGE(myMousePosition.myY, 1, myWindowHeight);
	}


	void InputWrapper::SetMouseSpeed(const float aMouseSpeed)
	{
		myMouseSpeed = aMouseSpeed;
		if (myMouseSpeed < 0.01f)
		{
			myMouseSpeed = 0.01f;
		}
	}


	void InputWrapper::SetMousePosition(const int aX, const int aY)
	{
		myMousePosition.myX = aX;
		myMousePosition.myY = aY;
	}


	void InputWrapper::CaptureWindowsMouse()
	{
		myWindowsMouseCapture = true;
		ShowCursor(false);
	}

	void InputWrapper::ReleaseWindowsMouse()
	{
		myWindowsMouseCapture = false;
		ShowCursor(true);
	}

	void InputWrapper::SwapWindowsMouseCaptureState()
	{
		myWindowsMouseCapture = !myWindowsMouseCapture;
		ShowCursor(myWindowsMouseCapture);
	}
	
	void InputWrapper::Update()
	{
		// Don't try to update if we haven't initialized direct input and devices
		if (myIsInitialized == false)
		{
			return;
		}

		SavePreviousInputStates();

		// Aquire mouse and keyboard input
		myDirectInputMouse->Acquire();
		myDirectInputKeyboard->Acquire();

		// Get mouse state
		myDirectInputMouse->GetDeviceState(sizeof(DIMOUSESTATE), static_cast<LPVOID>(&myMouseState));

		// Get keyboard state
		myDirectInputKeyboard->GetDeviceState(256, static_cast<LPVOID>(myKeyState));

		UpdateMousePosition();

		if (myWindowsMouseCapture == true)
		{
			KeepWindowsMouseInApp();
		}

		SendMessagesToObservers();
	}

	void InputWrapper::SendMessagesToObservers()
	{
		for (int i = 0; i < 256; ++i)
		{
			if (GetKeyPressed(static_cast<unsigned char>(i)) == true)
			{
				Notify(eMessageTypes::eKeyPressed, i);
			}
		}
	}



	void InputWrapper::KeepWindowsMouseInApp() const
	{
		RECT rect;
		GetWindowRect(myHWND, &rect);
		SetCursorPos(rect.left +  (myWindowWidth / 2), rect.top + (myWindowHeight / 2));
	}

	
	void InputWrapper::SavePreviousInputStates()
	{
		for (int i = 0; i < 255; ++i)
		{
			myPreviousKeyState[i] = myKeyState[i];
		}

		myPreviousMouseState = myMouseState;
	}


	bool InputWrapper::IsPressed(BYTE aValue) const
	{
		return ( (aValue & 0x80) > 0 );
	}
}
