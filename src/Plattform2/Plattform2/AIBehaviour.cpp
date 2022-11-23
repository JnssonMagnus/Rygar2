#include "stdafx.h"
#include "AIBehaviour.h"
#include "Megaton.h"
#include "World.h"
#include "PhysicBody.h"

void AIBehaviour::Update(PhysicBody& aPhysicBody)
{
	GoForward(aPhysicBody);
	TurnAtCliff(aPhysicBody);
	TurnAtWall(aPhysicBody);
}

void AIBehaviour::TurnAtCliff(PhysicBody& aPhysicBody)
{
	static const Vector2f oneDown(0, 1.f);
	auto& world = Megaton::GetInstance().GetWorld();
	if (aPhysicBody.GetDirection() == Vector2f(-1, 0) && world.PositionHasImpassibleTile(aPhysicBody.GetLeftBottom() + oneDown) == false)
		aPhysicBody.ChangeDirection();
	else if (aPhysicBody.GetDirection() == Vector2f(1, 0) && world.PositionHasImpassibleTile(aPhysicBody.GetRightBottom() + oneDown) == false)
		aPhysicBody.ChangeDirection();
}

void AIBehaviour::TurnAtWall(PhysicBody& aPhysicBody)
{
	if (aPhysicBody.GetDirection().myX < 0.f && aPhysicBody.HasPhysicState(ePhysicStates::eOnGround, PhysicBody::eLocator::eLeft) == true)
		aPhysicBody.ChangeDirection();
	else if (aPhysicBody.GetDirection().myX > 0.f && aPhysicBody.HasPhysicState(ePhysicStates::eOnGround, PhysicBody::eLocator::eRight) == true)
		aPhysicBody.ChangeDirection();
}

void AIBehaviour::GoForward(PhysicBody& aPhysicBody)
{
	aPhysicBody.AddForce(aPhysicBody.GetDirection() * 2.f);
}
