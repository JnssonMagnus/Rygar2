#include "stdafx.h"
#include "InputMapper.h"
#include "InputObserver.h"
#include "InputWrapper.h"
#include <assert.h>

namespace Input
{
	InputMapper* InputMapper::myInstance = nullptr;

	InputMapper::InputMapper()
	{
	}

	InputMapper::~InputMapper()
	{
	}

	void InputMapper::RunEvent(const eInputEvent aOutputEvent, const eInputState aState, const float aValue)
	{
		for (int i = 0; i < myObservers[aOutputEvent].Size(); ++i)
		{
			myObservers[aOutputEvent][i]->RecieveEvent(aOutputEvent, aState, aValue);
		}
	}

	void InputMapper::TranslateActionToEvent(const eInputAction aAction, const eInputState aState, const float aValue)
	{
		const auto eventIterator = myEvents.find(aAction);
		if (eventIterator != myEvents.end())
		{
			RunEvent(myEvents[aAction], aState, aValue);
		}
	}

	void InputMapper::UpdateOVRInput()
	{
#ifdef DirectXRenderer
		OVR::OVRWrapper* ovrWrapper = OVR::OVRWrapper::GetInstance();
		if (ovrWrapper->GetOVRInputState().IndexTrigger[static_cast<int>(OVR::eControllerID::eLeftController)] > 0.001f)
			TranslateActionToEvent(eInputAction::eOVR_L_IndexTriggerDown, ovrWrapper->GetOVRInputState().IndexTrigger[static_cast<int>(OVR::eControllerID::eLeftController)]);

		if (ovrWrapper->GetOVRInputState().IndexTrigger[static_cast<int>(OVR::eControllerID::eRightController)] > 0.001f)
			TranslateActionToEvent(eInputAction::eOVR_R_IndexTriggerDown, ovrWrapper->GetOVRInputState().IndexTrigger[static_cast<int>(OVR::eControllerID::eRightController)]);
#endif
	}

	void InputMapper::UpdateMouseInput()
	{
		Input::InputWrapper* wrapper = Input::InputWrapper::GetInstance();

		if (wrapper->GetMouseScroll())
			TranslateActionToEvent(eInputAction::eMouse_Scroll, eInputState::eDown, static_cast<float>(wrapper->GetMouseScroll()));
		if (wrapper->GetMouseButtonDown(eMouseButtons::eLeftMouseButton) == true)
			TranslateActionToEvent(eInputAction::eMouse_LeftButtonDown, eInputState::eDown, 1);
		if (wrapper->GetMouseButtonDown(eMouseButtons::eRightMouseButton) == true)
			TranslateActionToEvent(eInputAction::eMouse_RightButtonDown, eInputState::eDown, 1);

		if (wrapper->GetMouseButtonPressed(eMouseButtons::eLeftMouseButton) == true)
			TranslateActionToEvent(eInputAction::eMouse_LeftButtonPressed, eInputState::ePressed, 1);
		if (wrapper->GetMouseButtonPressed(eMouseButtons::eRightMouseButton) == true)
			TranslateActionToEvent(eInputAction::eMouse_RightButtonPressed, eInputState::ePressed, 1);

		if(wrapper->GetMouseDeltaPosition().myX != 0)
			TranslateActionToEvent(eInputAction::eMouse_MovedX, eInputState::eDown, static_cast<float>(wrapper->GetMouseDeltaPosition().myX));
		if (wrapper->GetMouseDeltaPosition().myY != 0)
			TranslateActionToEvent(eInputAction::eMouse_MovedY, eInputState::eDown, static_cast<float>(wrapper->GetMouseDeltaPosition().myY));
	}

	void InputMapper::UpdateKeyboardInput()
	{
		for (int keyCode = 0; keyCode < eInputAction::eLastKeyCode; keyCode++)
		{
			if (Input::InputWrapper::GetInstance()->GetKeyDown(keyCode) == true)
				TranslateActionToEvent(static_cast<eInputAction>(keyCode), eInputState::eDown, 1.f);
		}

		for (int keyCode = 0; keyCode < eInputAction::eLastKeyCode; keyCode++)
		{
			if (Input::InputWrapper::GetInstance()->GetKeyPressed(keyCode) == true)
				TranslateActionToEvent(static_cast<eInputAction>(keyCode), eInputState::ePressed, 1.f);
		}

		for (int keyCode = 0; keyCode < eInputAction::eLastKeyCode; keyCode++)
		{
			if (Input::InputWrapper::GetInstance()->GetKeyReleased(keyCode) == true)
				TranslateActionToEvent(static_cast<eInputAction>(keyCode), eInputState::eUp, 1.f);
		}
	}

	void InputMapper::UpdateControllerInput()
	{

	}

	void InputMapper::Update()
	{
#ifdef DirectXRenderer
		if (OVR::OVRWrapper::GetInstance()->IsInitiated() == true)
		{
			UpdateOVRInput();
		}
#endif
		UpdateMouseInput();
		UpdateKeyboardInput();
	}

	void InputMapper::MapEvent(const eInputAction aInputEvent, const eInputEvent aOutputEvent)
	{
		myEvents[aInputEvent] = aOutputEvent;
	}

	void InputMapper::AddObserver(const eInputEvent aEventToListenFor, InputObserver *aObserver)
	{
		assert(aObserver != nullptr && "InputObsever is nullptr!");
		assert(myObservers[aEventToListenFor].Find(aObserver) == -1 && "Observer already added!");
		myObservers[aEventToListenFor].Add(aObserver);
	}

	void InputMapper::RemoveObserver(const eInputEvent aEventToListenFor, InputObserver *aObserver)
	{
		assert(aObserver != nullptr && "InputObsever is nullptr!");
		myObservers[aEventToListenFor].RemoveCyclic(aObserver);
	}

	InputMapper* InputMapper::GetInstance()
	{
		assert(myInstance != nullptr && "InputMapper not created!");
		return myInstance;
	}

	void InputMapper::Create()
	{
		assert(myInstance == nullptr && "InputMapper already created!");
		myInstance = new InputMapper();
	}
	void InputMapper::Destroy()
	{
		assert(myInstance != nullptr && "InputMapper already destroyed or not created!");
		delete myInstance;
		myInstance = nullptr;
	}
}