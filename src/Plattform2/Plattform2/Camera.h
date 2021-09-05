#pragma once
#include <vector2.h>

class Camera
{
public:
	virtual void		Update() = 0;
	const Vector2f&		GetPosition() const;
	float				GetZoom() const;

protected:
	Vector2f			myPosition;
	float				myZoom = 1.f;

};

