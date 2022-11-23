#pragma once

template<class T>
class Vector2;

class Renderer;

class DebugDrawer
{
public:
	static void DrawLine(const Vector2<int>& aStart, const Vector2<int>& aEnd);
	static void SetRenderer(Renderer& aRenderer);
private:
	inline static Renderer* ourRenderer;

};

