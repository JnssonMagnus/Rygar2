#pragma once

#include <cmath>
//#include "commonMacros.h"

namespace CommonUtilities
{
	template <typename ObjectType>
	class Matrix33;
	template <typename ObjectType>
	class Matrix44;
}

namespace CU = CommonUtilities;

#define Vector3f Vector3<float>

template <typename ObjectType> 
class Vector3
{
public:
	Vector3(void) = default;
	Vector3(const ObjectType aX, const ObjectType aY, const ObjectType aZ);
	~Vector3(void) = default;

	Vector3 operator+(const Vector3& aVector);
	const Vector3 operator+(const Vector3& aVector) const;
	Vector3 operator-(const Vector3& aVector);
	const Vector3 operator-(const Vector3& aVector) const;
	Vector3 operator*(const Vector3& aVector);
	const Vector3 operator*(const Vector3& aVector) const;
	Vector3 operator/(const Vector3& aVector);
	const Vector3 operator/(const Vector3& aVector) const;

	const Vector3& operator+=(const Vector3& aVector);
	const Vector3& operator-=(const Vector3& aVector);
	const Vector3& operator*=(const Vector3& aVector);
	const Vector3& operator/=(const Vector3& aVector);

	void Set(const float aX, const float aY, const float aZ);
	
	Vector3 operator+(const ObjectType aType);
	const Vector3 operator+(const ObjectType aType) const;
	Vector3 operator-(const ObjectType aType);
	const Vector3 operator-(const ObjectType aType) const;
	Vector3 operator*(const ObjectType aType);
	const Vector3 operator*(const ObjectType aType) const;
	Vector3 operator/(const ObjectType aType);	
	const Vector3 operator/(const ObjectType aType) const;

	const Vector3& operator+=(const ObjectType aType);
	const Vector3& operator-=(const ObjectType aType);
	const Vector3& operator*=(const ObjectType aType);
	const Vector3& operator/=(const ObjectType aType);

	ObjectType Length();
	const ObjectType Length() const;
	ObjectType Length2();
	const ObjectType Length2() const;
	void Normalize();

	float DistanceTo(const Vector3 &aVector) const;

	ObjectType Dot(const Vector3& aVector);
	const ObjectType Dot(const Vector3& aVector) const;
	Vector3 Cross(const Vector3& aVector) const;

	Vector3& operator*=(const CommonUtilities::Matrix33<ObjectType> &aMatrix33);
	Vector3 operator*(const CommonUtilities::Matrix33<ObjectType> &aMatrix33) const;
	Vector3 operator*(const CommonUtilities::Matrix44<ObjectType> &aMatrix44);

	bool operator==(const Vector3<ObjectType> &aVector);
	const bool operator==(const Vector3<ObjectType> &aVector) const;

	Vector3 GetDirection();

	static const Vector3 Zero;

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

};

template <typename ObjectType>
Vector3<ObjectType>::Vector3(const ObjectType aX, const ObjectType aY, const ObjectType aZ)
:myX(aX)
,myY(aY)
,myZ(aZ)
{
}

template <typename ObjectType>
Vector3<ObjectType> Vector3<ObjectType>::operator+(const Vector3& aVector)
{
	Vector3<ObjectType> vec;
	vec.myX = myX + aVector.myX;
	vec.myY = myY + aVector.myY;
	vec.myZ = myZ + aVector.myZ;
	return vec;
}
template <typename ObjectType>
const Vector3<ObjectType> Vector3<ObjectType>::operator+(const Vector3& aVector) const
{
	Vector3<ObjectType> vec;
	vec.myX = myX + aVector.myX;
	vec.myY = myY + aVector.myY;
	vec.myZ = myZ + aVector.myZ;
	return vec;
}
template <typename ObjectType>
Vector3<ObjectType> Vector3<ObjectType>::operator-(const Vector3& aVector)
{
	Vector3<ObjectType> vec;
	vec.myX = myX - aVector.myX;
	vec.myY = myY - aVector.myY;
	vec.myZ = myZ - aVector.myZ;
	return vec;
}
template <typename ObjectType>
const Vector3<ObjectType> Vector3<ObjectType>::operator-(const Vector3& aVector) const
{
	Vector3<ObjectType> vec;
	vec.myX = myX - aVector.myX;
	vec.myY = myY - aVector.myY;
	vec.myZ = myZ - aVector.myZ;
	return vec;
}
template <typename ObjectType>
Vector3<ObjectType> Vector3<ObjectType>::operator*(const Vector3& aVector)
{
	Vector3<ObjectType> vec;
	vec.myX = myX * aVector.myX;
	vec.myY = myY * aVector.myY;
	vec.myZ = myZ * aVector.myZ;
	return vec;
}
template <typename ObjectType>
const Vector3<ObjectType> Vector3<ObjectType>::operator*(const Vector3& aVector) const
{
	Vector3<ObjectType> vec;
	vec.myX = myX * aVector.myX;
	vec.myY = myY * aVector.myY;
	vec.myZ = myZ * aVector.myZ;
	return vec;
}
template <typename ObjectType>
Vector3<ObjectType> Vector3<ObjectType>::operator/(const Vector3& aVector)
{
	Vector3<ObjectType> vec;
	vec.myX = myX / aVector.myX;
	vec.myY = myY / aVector.myY;
	vec.myZ = myZ / aVector.myZ;
	return vec;
}
template <typename ObjectType>
const Vector3<ObjectType> Vector3<ObjectType>::operator/(const Vector3& aVector) const
{
	Vector3<ObjectType> vec;
	vec.myX = myX / aVector.myX;
	vec.myY = myY / aVector.myY;
	vec.myZ = myZ / aVector.myZ;
	return vec;
}
template <typename ObjectType>
const Vector3<ObjectType>& Vector3<ObjectType>::operator+=(const Vector3& aVector)
{
	myX += aVector.myX;
	myY += aVector.myY;
	myZ += aVector.myZ;
	return *this;
}
template <typename ObjectType>
const Vector3<ObjectType>& Vector3<ObjectType>::operator-=(const Vector3& aVector)
{
	myX -= aVector.myX;
	myY -= aVector.myY;
	myZ -= aVector.myZ;
	return *this;
}

template <typename ObjectType>
Vector3<ObjectType>& Vector3<ObjectType>::operator*=(const CommonUtilities::Matrix33<ObjectType>& aMatrix)
{	
	ObjectType x = myX * aMatrix.myMatrix[0] + myY * aMatrix.myMatrix[3] + myZ * aMatrix.myMatrix[6];
	ObjectType y = myX * aMatrix.myMatrix[1] + myY * aMatrix.myMatrix[4] + myZ * aMatrix.myMatrix[7];
	ObjectType z = myX * aMatrix.myMatrix[2] + myY * aMatrix.myMatrix[5] + myZ * aMatrix.myMatrix[8];
	myX = x;
	myY = y;
	myZ = z;
	return *this;
}

template <typename ObjectType>
Vector3<ObjectType> Vector3<ObjectType>::operator*(const CommonUtilities::Matrix33<ObjectType>& aMatrix) const
{
	Vector3<ObjectType> result;
	result.myX = myX * aMatrix(1, 1) + myY * aMatrix(2, 1) + myZ * aMatrix(3, 1);
	result.myY = myX * aMatrix(1, 2) + myY * aMatrix(2, 2) + myZ * aMatrix(3, 2);
	result.myZ = myX * aMatrix(1, 3) + myY * aMatrix(2, 3) + myZ * aMatrix(3, 3);
	return result;
}

template <typename ObjectType>
const Vector3<ObjectType>& Vector3<ObjectType>::operator*=(const Vector3& aVector)
{
	myX *= aVector.myX;
	myY *= aVector.myY;
	myZ *= aVector.myZ;
	return *this;
}
template <typename ObjectType>
const Vector3<ObjectType>& Vector3<ObjectType>::operator/=(const Vector3& aVector)
{
	myX /= aVector.myX;
	myY /= aVector.myY;
	myZ /= aVector.myZ;
	return *this;
}

template <typename ObjectType>
Vector3<ObjectType> Vector3<ObjectType>::operator+(const ObjectType aType)
{
	Vector3<ObjectType> vec;
	vec.myX = myX + aType;
	vec.myY = myY + aType; 
	vec.myZ = myZ + aType; 
	return vec;
}
template <typename ObjectType>
const Vector3<ObjectType> Vector3<ObjectType>::operator+(const ObjectType aType) const
{
	Vector3<ObjectType> vec;
	vec.myX = myX + aType;
	vec.myY = myY + aType; 
	vec.myZ = myZ + aType; 
	return vec;
}
template <typename ObjectType>
Vector3<ObjectType> Vector3<ObjectType>::operator-(const ObjectType aType)
{
	Vector3<ObjectType> vec;
	vec.myX = myX - aType;
	vec.myY = myY - aType; 
	vec.myZ = myZ - aType; 
	return vec;
}
template <typename ObjectType>
const Vector3<ObjectType> Vector3<ObjectType>::operator-(const ObjectType aType) const
{
	Vector3<ObjectType> vec;
	vec.myX = myX - aType;
	vec.myY = myY - aType; 
	vec.myZ = myZ - aType; 
	return vec;
}
template <typename ObjectType>
Vector3<ObjectType> Vector3<ObjectType>::operator*(const ObjectType aType)
{
	Vector3<ObjectType> vec;
	vec.myX = myX * aType;
	vec.myY = myY * aType; 
	vec.myZ = myZ * aType; 
	return vec;
}
template <typename ObjectType>
const Vector3<ObjectType> Vector3<ObjectType>::operator*(const ObjectType aType) const
{
	Vector3<ObjectType> vec;
	vec.myX = myX * aType;
	vec.myY = myY * aType; 
	vec.myZ = myZ * aType; 
	return vec;
}
template <typename ObjectType>
Vector3<ObjectType> Vector3<ObjectType>::operator/(const ObjectType aType)
{
	Vector3<ObjectType> vec;
	vec.myX = myX / aType;
	vec.myY = myY / aType; 
	vec.myZ = myZ / aType; 
	return vec;
}
template <typename ObjectType>
const Vector3<ObjectType> Vector3<ObjectType>::operator/(const ObjectType aType) const
{
	Vector3<ObjectType> vec;
	vec.myX = myX / aType;
	vec.myY = myY / aType; 
	vec.myZ = myZ / aType; 
	return vec;
}
template <typename ObjectType>
const Vector3<ObjectType>& Vector3<ObjectType>::operator+=(const ObjectType aType)
{
	myX += aType;
	myY += aType;
	myZ += aType;
	return *this;
}
template <typename ObjectType>
const Vector3<ObjectType>& Vector3<ObjectType>::operator-=(const ObjectType aType)
{
	myX -= aType;
	myY -= aType;
	myZ -= aType;
	return *this;
}
template <typename ObjectType>
const Vector3<ObjectType>& Vector3<ObjectType>::operator*=(const ObjectType aType)
{
	myX *= aType;
	myY *= aType;
	myZ *= aType;
	return *this;
}
template <typename ObjectType>
const Vector3<ObjectType>& Vector3<ObjectType>::operator/=(const ObjectType aType)
{
	myX /= aType;
	myY /= aType;
	myZ /= aType;
	return *this;
}
template <typename ObjectType>
ObjectType Vector3<ObjectType>::Length()
{
	ObjectType retVal;
	retVal = sqrt(Length2());
	return retVal;
}
template <typename ObjectType>
const ObjectType Vector3<ObjectType>::Length() const
{
	ObjectType retVal;
	retVal = sqrt(Length2());
	return retVal;
}
template <typename ObjectType>
ObjectType Vector3<ObjectType>::Length2()
{
	ObjectType retVal;
	retVal = (myX * myX + myY * myY + myZ * myZ);
	return retVal;
}
template <typename ObjectType>
const ObjectType Vector3<ObjectType>::Length2() const
{
	ObjectType retVal;
	retVal = (myX * myX + myY * myY + myZ * myZ);
	return retVal;
}
template <typename ObjectType>
void Vector3<ObjectType>::Normalize()
{
	ObjectType hypotenuse = Length();
	myX /= hypotenuse;
	myY /= hypotenuse;
	myZ /= hypotenuse;
}
template <typename ObjectType>
ObjectType Vector3<ObjectType>::Dot(const Vector3& aVector)
{
	return (myX * aVector.myX + myY * aVector.myY + myZ * aVector.myZ);
}
template <typename ObjectType>
const ObjectType Vector3<ObjectType>::Dot(const Vector3& aVector) const
{
	return (myX * aVector.myX + myY * aVector.myY + myZ * aVector.myZ);
}
template <typename ObjectType>
Vector3<ObjectType> Vector3<ObjectType>::Cross(const Vector3& aVector) const
{
	Vector3<ObjectType> vec;
	vec.myX = myY * aVector.myZ - myZ * aVector.myY;
	vec.myY = myZ * aVector.myX - myX * aVector.myZ;
	vec.myZ = myX * aVector.myY - myY * aVector.myX;
	return vec;
}
template <typename ObjectType>
bool Vector3<ObjectType>::operator==(const Vector3<ObjectType> &aVector)
{
	if(myX != aVector.myX)
	{
		return false;
	}
	if(myY != aVector.myY)
	{
		return false;
	}
	if(myZ != aVector.myZ)
	{
		return false;
	}
	return true;
}
template <typename ObjectType>
const bool Vector3<ObjectType>::operator==(const Vector3<ObjectType> &aVector) const
{
	if(myX != aVector.myX)
	{
		return false;
	}
	if(myY != aVector.myY)
	{
		return false;
	}
	if(myZ != aVector.myZ)
	{
		return false;
	}
	return true;
}
template <typename ObjectType>
Vector3<ObjectType> Vector3<ObjectType>::GetDirection()
{
	Vector3<ObjectType> vector = *this;
	vector.Normalize();
	return vector;
}
template<typename ObjectType>
void Vector3<ObjectType>::Set(const float aX, const float aY, const float aZ)
{
	myX = aX;
	myY = aY;
	myZ = aZ;
}

template <typename ObjectType>
float Vector3<ObjectType>::DistanceTo(const Vector3 &aVector) const
{
	return sqrt(pow(myX - aVector.myX, 2) + pow(myY - aVector.myY, 2) + pow(myZ - aVector.myZ, 2));
}

template <class T>
const Vector3<T> Vector3<T>::Zero = Vector3<T>(0, 0, 0);

