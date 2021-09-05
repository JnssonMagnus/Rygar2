#include "stdafx.h"
#include "MathUtils.h"

namespace MathUtils
{
	Vector3<float> GetBinormal(const Vector4<float>& aVertex1, const Vector4<float>& aVertex2, const Vector4<float>& aVertex3,
		const Vector2<float>& aUV1, const Vector2<float>& aUV2, const Vector2<float>& aUV3)
	{
		Vector3<float> binormal;

		Vector4<float> faceVector1 = aVertex2 - aVertex1;
		Vector4<float> faceVector2 = aVertex3 - aVertex1;

		Vector2<float> uv0 = aUV2 - aUV1;
		Vector2<float> uv1 = aUV3 - aUV1;

		float denominator = 1.f / (uv0.u * uv1.v - uv1.u * uv0.v);

		float vector1[3], vector2[3];
		float tuVector[2], tvVector[2];
		vector1[0] = faceVector1.x;
		vector1[1] = faceVector1.y;
		vector1[2] = faceVector1.z;

		vector2[0] = faceVector2.x;
		vector2[1] = faceVector2.y;
		vector2[2] = faceVector2.z;

		tuVector[0] = uv0.x;
		tuVector[1] = uv1.x;

		tvVector[0] = uv0.y;
		tvVector[1] = uv1.y;

		binormal.x = (tuVector[0] * vector2[0] - tuVector[1] * vector1[0]) * denominator;
		binormal.y = (tuVector[0] * vector2[1] - tuVector[1] * vector1[1]) * denominator;
		binormal.z = (tuVector[0] * vector2[2] - tuVector[1] * vector1[2]) * denominator;

		binormal.Normalize();

		return binormal;
	}

	CU::Matrix44<float> GetMatrix44FromQuaternion(const float aX, const float aY, const float aZ, const float aW)
	{
		CU::Matrix44<float> m;
		m.myMatrix[0] = 1 - 2 * aY*aY - 2 * aZ*aZ;
		m.myMatrix[1] = 2 * aX*aY - 2 * aZ*aW;
		m.myMatrix[2] = 2 * aX*aZ + 2 * aY*aW;
		m.myMatrix[3] = 0;

		m.myMatrix[4] = 2 * aX*aY + 2 * aZ*aW;
		m.myMatrix[5] = 1 - 2 * aX*aX - 2 * aZ*aZ;
		m.myMatrix[6] = 2 * aY*aZ - 2 * aX*aW;
		m.myMatrix[7] = 0;

		m.myMatrix[8] = 2 * aX*aZ - 2 * aY*aW;
		m.myMatrix[9] = 2 * aY*aZ + 2 * aX*aW;
		m.myMatrix[10] = 1 - 2 * aX*aX - 2 * aY*aY;		
		m.myMatrix[11] = 1;

		return m;
	}
}