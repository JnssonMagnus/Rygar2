#pragma once

class PhysicBody;

class PhysicBodyVisitor
{
public:
	virtual void Accept(PhysicBody& aPhysicBody) = 0;
};


