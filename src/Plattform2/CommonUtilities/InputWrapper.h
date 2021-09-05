#pragma once

#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#include <dinput.h>
#include "PostMaster/Subject.h"

namespace Input
{
	struct Position
	{
		LONG myX;
		LONG myY;
	};

	enum class eMouseButtons
	{
		eLeftMouseButton,
		eRightMouseButton,
		eMiddleMouseButton
	};

	class InputWrapper : public Subject
	{
	public:
		bool GetKeyPressed(unsigned char aKey) const;
		bool GetKeyReleased(unsigned char aKey) const;
		bool GetKeyDown(unsigned char aKey) const;

		bool GetMouseButtonDown(const eMouseButtons aMouseButton) const;
		bool GetMouseButtonPressed(const eMouseButtons aMouseButton) const;
		bool GetMouseButtonReleased(const eMouseButtons aMouseButton) const;

		Position GetMousePosition() const;
		Position GetMouseDeltaPosition() const;
		Position GetMouseDeltaPositionInPixels() const;

		LONG GetMouseScroll() const;
		void SetMouseSpeed(const float aMouseSpeed);
		void SetMousePosition(const int aX, const int aY);

		void Init(HINSTANCE aHInstance, HWND aHWND, int aWindowWidth, int aWindowHeight);
		void Update();

		inline bool IsInitialized() const;

		void CaptureWindowsMouse();
		void ReleaseWindowsMouse();
		void SwapWindowsMouseCaptureState();

		static InputWrapper*	GetInstance();
		void					Destroy();

	private:
		InputWrapper();
		~InputWrapper();

		static InputWrapper* myInstance;

		LPDIRECTINPUT8 myDirectInput; // Pointer to Direct Input 
		LPDIRECTINPUTDEVICE8 myDirectInputKeyboard; // Pointer to keyboard device
		LPDIRECTINPUTDEVICE8 myDirectInputMouse; // Pointer to mouse device
	
		DIMOUSESTATE myMouseState; // A struct with mouse delta positions and button states
		DIMOUSESTATE myPreviousMouseState; // State of mouse last frame

		BYTE myKeyState[256]; // State of each key
		BYTE myPreviousKeyState[256]; // State of each key from last update

		void SavePreviousInputStates();
		bool IsPressed(BYTE aValue) const;

		void UpdateMousePosition();

		void KeepWindowsMouseInApp() const;

		void SendMessagesToObservers();

		bool myIsInitialized;
		Position myMousePosition;
		Position myOldMousePosition;

		int myWindowWidth;
		int myWindowHeight;

		float myMouseSpeed;
		bool myWindowsMouseCapture;

		HWND myHWND;
	};

	bool InputWrapper::IsInitialized() const
	{
		return myIsInitialized;
	}
}
