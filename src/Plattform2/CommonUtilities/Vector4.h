#ifndef VECTOR4_H
#define VECTOR4_H

#ifndef MATRIX44DECL_H
#include "Matrix44decl.h"
#endif

#include <cmath>
#include <intrin.h>

#pragma warning(disable: 4201) // nameless struct/union warning. non standard (standard in C++ 11 but may not be implemented)

#define Vector4f Vector4<float>

template <typename ObjectType> class Vector4
{
public:
	Vector4(const ObjectType aX, const ObjectType aY, const ObjectType aZ, const ObjectType aW);
	Vector4(void) = default;
	~Vector4(void) = default;

	Vector4 operator+(const Vector4& aVector) const;
	Vector4 operator-(const Vector4& aVector) const;
	Vector4 operator*(const Vector4& aVector) const;
	Vector4 operator/(const Vector4& aVector) const;

	const Vector4& operator+=(const Vector4& aVector);
	const Vector4& operator-=(const Vector4& aVector);
	const Vector4& operator*=(const Vector4& aVector);
	const Vector4& operator/=(const Vector4& aVector);
	
	Vector4 operator+(const ObjectType aType) const;
	Vector4 operator-(const ObjectType aType) const;
	Vector4 operator*(const ObjectType aType) const;
	Vector4 operator/(const ObjectType aType) const;	

	const Vector4& operator+=(const ObjectType aType);
	const Vector4& operator-=(const ObjectType aType);
	const Vector4& operator*=(const ObjectType aType);
	const Vector4& operator/=(const ObjectType aType);

	ObjectType Length();
	ObjectType Length2();

	static const Vector4 Zero;

	void Normalize();

	void Set(const float aX, const float aY, const float aZ, const float aW);

	ObjectType Dot(const Vector4& aVector) const;

	Vector4 operator*(const CommonUtilities::Matrix44<ObjectType>& aMatrix44) const;

	//__declspec(align(16))
	union
	{
		__m128 mySSE2Data;
		struct
		{
			union
			{
				ObjectType myX;
				ObjectType x;
				ObjectType r;
				ObjectType myR;
			};
			union
			{
				ObjectType myY;
				ObjectType y;
				ObjectType g;
				ObjectType myG;
			};
			union
			{
				ObjectType myZ;
				ObjectType z;
				ObjectType b;
				ObjectType myB;
			};
			union
			{
				ObjectType myW;
				ObjectType w;
				ObjectType a;
				ObjectType myA;
			};
		};
	};

};

template <typename ObjectType>
Vector4<ObjectType>::Vector4(const ObjectType aX, const ObjectType aY, const ObjectType aZ, const ObjectType aW)
:myX(aX)
,myY(aY)
,myZ(aZ)
,myW(aW)
{
}

template <typename ObjectType>
Vector4<ObjectType> Vector4<ObjectType>::operator+(const Vector4& aVector) const
{

	Vector4<ObjectType> vec;
	vec.mySSE2Data = _mm_add_ps(mySSE2Data, aVector.mySSE2Data);
	return vec;
}
template <typename ObjectType>
Vector4<ObjectType> Vector4<ObjectType>::operator-(const Vector4& aVector) const
{
	Vector4<ObjectType> vec;
	vec.mySSE2Data = _mm_sub_ps(mySSE2Data, aVector.mySSE2Data);
	return vec;
}
template <typename ObjectType>
Vector4<ObjectType> Vector4<ObjectType>::operator*(const Vector4& aVector) const
{
	Vector4<ObjectType> vec;
	vec.mySSE2Data = _mm_mul_ps(mySSE2Data, aVector.mySSE2Data);
	return vec;
}
template <typename ObjectType>
Vector4<ObjectType> Vector4<ObjectType>::operator/(const Vector4& aVector) const
{
	Vector4<ObjectType> vec;
	vec.mySSE2Data = _mm_div_ps(mySSE2Data, aVector.mySSE2Data);
	return vec;
}
template <typename ObjectType>
const Vector4<ObjectType>& Vector4<ObjectType>::operator+=(const Vector4& aVector)
{
	mySSE2Data = _mm_add_ps(mySSE2Data, aVector.mySSE2Data);
	return *this;
}
template <typename ObjectType>
const Vector4<ObjectType>& Vector4<ObjectType>::operator-=(const Vector4& aVector)
{
	mySSE2Data = _mm_sub_ps(mySSE2Data, aVector.mySSE2Data);
	return *this;
}
template <typename ObjectType>
const Vector4<ObjectType>& Vector4<ObjectType>::operator*=(const Vector4& aVector)
{
	mySSE2Data = _mm_mul_ps(mySSE2Data, aVector.mySSE2Data);
	return *this;
}
template <typename ObjectType>
const Vector4<ObjectType>& Vector4<ObjectType>::operator/=(const Vector4& aVector)
{
	mySSE2Data = _mm_div_ps(mySSE2Data, aVector.mySSE2Data);
	return *this;
}

template <typename ObjectType>
Vector4<ObjectType> Vector4<ObjectType>::operator+(const ObjectType aType) const
{
	Vector4<ObjectType> vec;
	vec.mySSE2Data = _mm_set_ps1(aType);
	vec.mySSE2Data = _mm_add_ps(vec.mySSE2Data, mySSE2Data);
	return vec;
}
template <typename ObjectType>
Vector4<ObjectType> Vector4<ObjectType>::operator-(const ObjectType aType) const
{
	Vector4<ObjectType> vec;
	vec.mySSE2Data = _mm_set_ps1(aType);
	vec.mySSE2Data = _mm_sub_ps(vec.mySSE2Data, mySSE2Data);
	return vec;
}
template <typename ObjectType>
Vector4<ObjectType> Vector4<ObjectType>::operator*(const ObjectType aType) const
{
	Vector4<ObjectType> vec;
	vec.mySSE2Data = _mm_set_ps1(aType);
	vec.mySSE2Data = _mm_mul_ps(vec.mySSE2Data, mySSE2Data);
	return vec;
}
template <typename ObjectType>
Vector4<ObjectType> Vector4<ObjectType>::operator/(const ObjectType aType) const
{
	Vector4<ObjectType> vec;
	vec.mySSE2Data = _mm_set_ps1(aType);
	vec.mySSE2Data = _mm_mul_ps(mySSE2Data, vec.mySSE2Data);
	return vec;
}
template <typename ObjectType>
const Vector4<ObjectType>& Vector4<ObjectType>::operator+=(const ObjectType aType)
{
	Vector4<ObjectType> vec;
	vec.mySSE2Data = _mm_set_ps1(aType);
	mySSE2Data = _mm_add_ps(mySSE2Data, vec.mySSE2Data);
	return *this;
}
template <typename ObjectType>
const Vector4<ObjectType>& Vector4<ObjectType>::operator-=(const ObjectType aType)
{
	Vector4<ObjectType> vec;
	vec.mySSE2Data = _mm_set_ps1(aType);
	mySSE2Data = _mm_sub_ps(mySSE2Data, vec.mySSE2Data);
	return *this;
}
template <typename ObjectType>
const Vector4<ObjectType>& Vector4<ObjectType>::operator*=(const ObjectType aType)
{
	Vector4<ObjectType> vec;
	vec.mySSE2Data = _mm_set_ps1(aType);
	mySSE2Data = _mm_mul_ps(vec.mySSE2Data, mySSE2Data);
	return *this;
}
template <typename ObjectType>
const Vector4<ObjectType>& Vector4<ObjectType>::operator/=(const ObjectType aType)
{
	Vector4<ObjectType> vec;
	vec.mySSE2Data = _mm_set_ps1(aType);
	mySSE2Data = _mm_div_ps(mySSE2Data, vec.mySSE2Data);
	return *this;
}
template <typename ObjectType>
ObjectType Vector4<ObjectType>::Length()
{
	ObjectType retVal;
	retVal = sqrt(Length2());
	return retVal;
}
template <typename ObjectType>
ObjectType Vector4<ObjectType>::Length2()
{
	return Dot(*this);
}
template <typename ObjectType>
void Vector4<ObjectType>::Normalize()
{
	ObjectType hypotenuse = Length();
	*this /= hypotenuse;
}
template <typename ObjectType>
ObjectType Vector4<ObjectType>::Dot(const Vector4& aVector) const
{
	return _mm_dp_ps(mySSE2Data, aVector.mySSE2Data, 0xff).m128_f32[0];
}

template <typename ObjectType>
void Vector4<ObjectType>::Set(const float aX, const float aY, const float aZ, const float aW)
{
	myX = aX;
	myY = aY;
	myZ = aZ;
	myW = aW;
}

template<typename T>
Vector4<T> Vector4<T>::operator*(const CommonUtilities::Matrix44<T>& aMatrix44) const
{
	Vector4<T> result;
	result.x = (myX * aMatrix44.myMatx[0][0]) + (myY * aMatrix44.myMatx[0][1]) + (myZ * aMatrix44.myMatx[0][2]) + (myW * aMatrix44.myMatx[0][3]);
	result.y = (myX * aMatrix44.myMatx[1][0]) + (myY * aMatrix44.myMatx[1][1]) + (myZ * aMatrix44.myMatx[1][2]) + (myW * aMatrix44.myMatx[1][3]);
	result.z = (myX * aMatrix44.myMatx[2][0]) + (myY * aMatrix44.myMatx[2][1]) + (myZ * aMatrix44.myMatx[2][2]) + (myW * aMatrix44.myMatx[2][3]);
	result.w = (myX * aMatrix44.myMatx[3][0]) + (myY * aMatrix44.myMatx[3][1]) + (myZ * aMatrix44.myMatx[3][2]) + (myW * aMatrix44.myMatx[3][3]);
	return result;
}

template <class T>
const Vector4<T> Vector4<T>::Zero = Vector4<T>(0, 0, 0, 0);

#endif