#pragma once
#include "Visitor.h"

class CollisionBoxDrawerVisitor : public PhysicBodyVisitor
{
public:
	CollisionBoxDrawerVisitor();
	void Accept(PhysicBody& aPhysicBody) override;

private:
};

