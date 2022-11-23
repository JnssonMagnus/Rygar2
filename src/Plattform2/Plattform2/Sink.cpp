#include "stdafx.h"
#include "Sink.h"
#include "Megaton.h"
#include "MapChunk.h"

Sink::Sink()
{
	mySinkPerFrame = 10_uc;
}

void Sink::Update(const float aDeltaTime)
{
	Megaton::GetInstance().GetMap().TryTakeWater(mySinkPerFrame, myPhysicBody->GetPosition());
}
