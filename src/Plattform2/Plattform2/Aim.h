#pragma once
#include "Sprite.h"
#include "../CommonUtilities/InputObserver.h"
#include "../CommonUtilities/PostMaster/Observer.h"

class Aim : public Input::InputObserver, public Observer
{
public:
						Aim(const Aim&) = delete;
						Aim() = default;
	const Aim&			operator=(const Aim&) = delete;

	void				RecieveEvent(const Input::eInputEvent aEvent, const Input::eInputState aState, const float aValue) override;
	void				RecieveMessage(const Message& aMessage) override;

	void				Init();
	void				Draw();
	const Vector2f		GetPosition() const;
	const Vector2f		GetLocalPosition() const;

private:
	Sprite				mySprite;
	Vector2f			myLocalPosition = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	Vector2f			myWorldOffset = { 0.f, 0.f };
	float				mySpeed = 0.8f;
};

