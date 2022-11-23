#include "stdafx.h"
#include "DebugDrawer.h"
#include "Renderer.h"

void DebugDrawer::DrawLine(const Vector2<int>& aStart, const Vector2<int>& aEnd)
{
	ourRenderer->AddDebugLine(aStart, aEnd);
}

void DebugDrawer::SetRenderer(Renderer& aRenderer)
{
	ourRenderer = &aRenderer;
}
