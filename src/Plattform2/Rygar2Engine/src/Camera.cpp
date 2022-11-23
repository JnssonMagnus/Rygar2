#include "stdafx.h"
#include "Camera.h"

const Vector2f& Camera::GetPosition() const
{
	return myPosition;
}

float Camera::GetZoom() const
{
	return myZoom;
}
