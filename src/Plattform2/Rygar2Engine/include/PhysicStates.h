#pragma once

enum class ePhysicStates
{
	eOnGround = 1,
	eInAir = 1 << 1,
	eInWater = 1 << 2,
};
