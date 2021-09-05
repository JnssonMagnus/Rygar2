#pragma once
#include "InputMapperEvents.h"
#include <GrowingArray.h>
#include <unordered_map>

namespace Input
{
	class InputObserver;

	class InputMapper
	{
	public:

		void					Update();
		void					MapEvent(const eInputAction aInputEvent, const eInputEvent aOutputEvent);
		void					AddObserver(const eInputEvent aEventToListenFor, InputObserver* aObserver);
		void					RemoveObserver(const eInputEvent aEventToListenFor, InputObserver* aObserver);
		static InputMapper*		GetInstance();
		static void				Create();
		static void				Destroy();


	private:
								InputMapper();
								~InputMapper();

		void					RunEvent(const eInputEvent aOutputEvent, const eInputState aState, const float aValue = 0);
		void					TranslateActionToEvent(const eInputAction aAction, const eInputState aState, const float aValue = 0);

		void					UpdateOVRInput();
		void					UpdateMouseInput();
		void					UpdateKeyboardInput();
		void					UpdateControllerInput();

		std::unordered_map<eInputEvent, CU::GrowingArray<InputObserver*>>
								myObservers;

		std::unordered_map<eInputAction, eInputEvent>
								myEvents;

		static InputMapper*		myInstance;
	};
}