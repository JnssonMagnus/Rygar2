#pragma once
#include "Vector.h"
#include "Matrix44decl.h"

namespace MathUtils
{
	Vector3<float> GetBinormal(const Vector4<float>& aVertex1, const Vector4<float>& aVertex2, const Vector4<float>& aVertex3,
		const Vector2<float>& aUV1, const Vector2<float>& aUV2, const Vector2<float>& aUV3);

	CU::Matrix44<float> GetMatrix44FromQuaternion(const float aX, const float aY, const float aZ, const float aW);

	template<class T>
	T Lerp(const T& aValue1, const T& aValue2, const float aPercent)
	{
		assert(aPercent >= 0.f && aPercent <= 1.f && "Lerp only 0-1!");
		return (1 - aPercent) * aValue1 + aPercent * aValue2;
	}
}