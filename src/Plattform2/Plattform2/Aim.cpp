#include "stdafx.h"
#include "Aim.h"
#include "../CommonUtilities/InputMapper.h"

void Aim::RecieveEvent(const Input::eInputEvent aEvent, const Input::eInputState aState, const float aValue)
{
    switch (aEvent)
    {
    case Input::eInputEvent::eAimX:
        myLocalPosition.myX += aValue * mySpeed;
        break;
    case Input::eInputEvent::eAimY:
        myLocalPosition.myY += aValue * mySpeed;
        break;
    }

    myLocalPosition.myX = RANGE(myLocalPosition.myX, 0, SCREEN_WIDTH);
    myLocalPosition.myY = RANGE(myLocalPosition.myY, 0, SCREEN_HEIGHT);        
}

void Aim::RecieveMessage(const Message& aMessage)
{
    myWorldOffset = aMessage.myPosition;
}

void Aim::Init()
{
    Input::InputMapper::GetInstance()->AddObserver(Input::eInputEvent::eAimX, this);
    Input::InputMapper::GetInstance()->AddObserver(Input::eInputEvent::eAimY, this);

    PostMaster::GetInstance()->Register(this, eMessageTypes::eCameraMoved);
    mySprite.Init("data/gfx/aim.png");
    mySprite.CenterPivot();
}

void Aim::Draw()
{
    mySprite.Draw(GetPosition(), 0.f, true);
}

const Vector2f Aim::GetPosition() const
{
    return myLocalPosition + myWorldOffset - Vector2f{ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
}

const Vector2f Aim::GetLocalPosition() const
{
    return myLocalPosition - Vector2f{ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
}
