#include "stdafx.h"
#include "CollisionBoxDrawerVisitor.h"
#include "DebugDrawer.h"
#include "GameObject.h"
#include "PhysicBody.h"
#include "Megaton.h"

CollisionBoxDrawerVisitor::CollisionBoxDrawerVisitor()
{
}

void CollisionBoxDrawerVisitor::Accept(PhysicBody& aPhysicBody)
{
	DebugDrawer::DrawLine(aPhysicBody.GetLeftTop(), aPhysicBody.GetRightTop());
	DebugDrawer::DrawLine(aPhysicBody.GetRightTop(), aPhysicBody.GetRightBottom());
	DebugDrawer::DrawLine(aPhysicBody.GetRightBottom(), aPhysicBody.GetLeftBottom());
	DebugDrawer::DrawLine(aPhysicBody.GetLeftBottom(), aPhysicBody.GetLeftTop());
}
