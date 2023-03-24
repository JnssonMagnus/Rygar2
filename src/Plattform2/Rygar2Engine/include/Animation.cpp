#include "stdafx.h"
#include "Animation.h"

eAnimationID GetAnimationEnum(const char* str)
{
    if (strcmp(str, "Default") == 0)
        return eAnimationID::eDefault;
    else if (strcmp(str, "Idle") == 0)
        return eAnimationID::eIdle;
    else if (strcmp(str, "Walk") == 0)
        return eAnimationID::eWalk;
    else if (strcmp(str, "Jump") == 0)
        return eAnimationID::eJump;
    else if (strcmp(str, "Attack") == 0)
        return eAnimationID::eAttack;
    else if (strcmp(str, "DuckAttack") == 0)
        return eAnimationID::eDuckAttack;
    else if (strcmp(str, "JumpAttack") == 0)
        return eAnimationID::eJumpAttack;
    else if (strcmp(str, "Fall") == 0)
        return eAnimationID::eFall;
    else if (strcmp(str, "Stagger") == 0)
        return eAnimationID::eStagger;
    else if (strcmp(str, "Dead") == 0)
        return eAnimationID::eDead;
    else if (strcmp(str, "DuckIdle") == 0)
        return eAnimationID::eDuckIdle;
    else if (strcmp(str, "ThrowHook") == 0)
        return eAnimationID::eThrowHook;

    return eAnimationID();
}
