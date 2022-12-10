#pragma once
#include <cmath>

template <typename ObjectType> class Vector2
{
public:
	Vector2(void);
	Vector2(const ObjectType aX, const ObjectType aY);
	~Vector2(void);

	template<class toType>
	Vector2(const Vector2<toType>& aAnotherType);

	Vector2 operator+(const Vector2& aVector) const;
	Vector2 operator-(const Vector2& aVector) const;
	Vector2 operator*(const Vector2& aVector) const;
	Vector2 operator/(const Vector2& aVector) const;

	const Vector2& operator+=(const Vector2& aVector);
	const Vector2& operator-=(const Vector2& aVector);
	const Vector2& operator*=(const Vector2& aVector);
	const Vector2& operator/=(const Vector2& aVector);
	
	Vector2 operator+(const ObjectType aType) const;
	Vector2 operator-(const ObjectType aType) const;
	Vector2 operator*(const ObjectType aType) const;
	Vector2 operator/(const ObjectType aType) const;	

	const Vector2& operator+=(const ObjectType aType);
	const Vector2& operator-=(const ObjectType aType);
	const Vector2& operator*=(const ObjectType aType);
	const Vector2& operator/=(const ObjectType aType);

	bool operator==(const Vector2 &aVector) const;
	bool operator!=(const Vector2 &aVector) const;

	float SqrdDistanceTo(const Vector2 &aVector) const;
	float DistanceTo(const Vector2& aVector) const;

	ObjectType Length() const;
	ObjectType Length2() const;
	void Normalize();
	Vector2 GetNormalized() const;

	ObjectType Dot(const Vector2& aVector);

	union
	{
		ObjectType myX;
		ObjectType x;
		ObjectType u;
		ObjectType min;
	};
	union
	{
		ObjectType myY;
		ObjectType y;
		ObjectType v;
		ObjectType max;
	};

};
template <typename ObjectType>
Vector2<ObjectType>::Vector2(void) : myX(0), myY(0)
{
}

template <typename ObjectType>
Vector2<ObjectType>::Vector2(const ObjectType aX, const ObjectType aY) : myX(aX), myY(aY)
{
}

template <typename ObjectType>
Vector2<ObjectType>::~Vector2(void)
{
}
template <typename ObjectType>
Vector2<ObjectType> Vector2<ObjectType>::operator+(const Vector2& aVector) const
{
	Vector2<ObjectType> vec;
	vec.myX = myX + aVector.myX;
	vec.myY = myY + aVector.myY;
	return vec;
}
template <typename ObjectType>
Vector2<ObjectType> Vector2<ObjectType>::operator-(const Vector2& aVector) const
{
	Vector2<ObjectType> vec;
	vec.myX = myX - aVector.myX;
	vec.myY = myY - aVector.myY;
	return vec;
}
template <typename ObjectType>
Vector2<ObjectType> Vector2<ObjectType>::operator*(const Vector2& aVector) const
{
	Vector2<ObjectType> vec;
	vec.myX = myX * aVector.myX;
	vec.myY = myY * aVector.myY;
	return vec;
}
template <typename ObjectType>
Vector2<ObjectType> Vector2<ObjectType>::operator/(const Vector2& aVector) const
{
	Vector2<ObjectType> vec;
	vec.myX = myX / aVector.myX;
	vec.myY = myY / aVector.myY;
	return vec;
}
template <typename ObjectType>
const Vector2<ObjectType>& Vector2<ObjectType>::operator+=(const Vector2& aVector)
{
	myX += aVector.myX;
	myY += aVector.myY;
	return *this;
}
template <typename ObjectType>
const Vector2<ObjectType>& Vector2<ObjectType>::operator-=(const Vector2& aVector)
{
	myX -= aVector.myX;
	myY -= aVector.myY;
	return *this;
}
template <typename ObjectType>
const Vector2<ObjectType>& Vector2<ObjectType>::operator*=(const Vector2& aVector)
{
	myX *= aVector.myX;
	myY *= aVector.myY;
	return *this;
}
template <typename ObjectType>
const Vector2<ObjectType>& Vector2<ObjectType>::operator/=(const Vector2& aVector)
{
	myX /= aVector.myX;
	myY /= aVector.myY;
	return *this;
}

template <typename ObjectType>
Vector2<ObjectType> Vector2<ObjectType>::operator+(const ObjectType aType) const
{
	Vector2<ObjectType> vec;
	vec.myX = myX + aType;
	vec.myY = myY + aType; 
	return vec;
}
template <typename ObjectType>
Vector2<ObjectType> Vector2<ObjectType>::operator-(const ObjectType aType) const
{
	Vector2<ObjectType> vec;
	vec.myX = myX - aType;
	vec.myY = myY - aType; 
	return vec;
}
template <typename ObjectType>
Vector2<ObjectType> Vector2<ObjectType>::operator*(const ObjectType aType) const
{
	Vector2<ObjectType> vec;
	vec.myX = myX * aType;
	vec.myY = myY * aType; 
	return vec;
}
template <typename ObjectType>
Vector2<ObjectType> Vector2<ObjectType>::operator/(const ObjectType aType) const
{
	Vector2<ObjectType> vec;
	vec.myX = myX / aType;
	vec.myY = myY / aType; 
	return vec;
}
template <typename ObjectType>
const Vector2<ObjectType>& Vector2<ObjectType>::operator+=(const ObjectType aType)
{
	myX += aType;
	myY += aType;
	return *this;
}
template <typename ObjectType>
const Vector2<ObjectType>& Vector2<ObjectType>::operator-=(const ObjectType aType)
{
	myX -= aType;
	myY -= aType;
	return *this;
}
template <typename ObjectType>
const Vector2<ObjectType>& Vector2<ObjectType>::operator*=(const ObjectType aType)
{
	myX *= aType;
	myY *= aType;
	return *this;
}
template <typename ObjectType>
const Vector2<ObjectType>& Vector2<ObjectType>::operator/=(const ObjectType aType)
{
	myX /= aType;
	myY /= aType;
	return *this;
}
template <typename ObjectType>
ObjectType Vector2<ObjectType>::Length() const
{
	ObjectType retVal;
	retVal = sqrt(Length2());
	return retVal;
}
template <typename ObjectType>
ObjectType Vector2<ObjectType>::Length2() const
{
	ObjectType retVal;
	retVal = (myX * myX + myY * myY);
	return retVal;
}
template <typename ObjectType>
void Vector2<ObjectType>::Normalize()
{
	ObjectType hypotenuse = Length();
	myX /= hypotenuse;
	myY /= hypotenuse;
}

template <typename ObjectType>
Vector2<ObjectType> Vector2<ObjectType>::GetNormalized() const
{
	Vector2 normalized = *this;
	normalized.Normalize();
	return normalized;
}


template <typename ObjectType>
ObjectType Vector2<ObjectType>::Dot(const Vector2& aVector)
{
	ObjectType returnValue = (myX * aVector.myX + myY * aVector.myY);
	return returnValue;
}
template <typename ObjectType>
bool Vector2<ObjectType>::operator==(const Vector2 &aVector) const
{
	if(myX != aVector.myX)
	{
		return false;
	}
	if(myY != aVector.myY)
	{
		return false;
	}
	return true;
}

template <typename ObjectType>
bool Vector2<ObjectType>::operator!=(const Vector2 &aVector) const
{
	return !((*this) == aVector);
}

template <typename ObjectType>
inline float Vector2<ObjectType>::DistanceTo(const Vector2 &aVector) const
{
	return sqrt(pow(myX - aVector.myX, 2) + pow(myY - aVector.myY, 2));
}

template <typename ObjectType>
float Vector2<ObjectType>::SqrdDistanceTo(const Vector2& aVector) const
{
	return static_cast<float>(pow(myX - aVector.myX, 2) + pow(myY - aVector.myY, 2));
}

template<class T>
template<class toType>
Vector2<T>::Vector2(const Vector2<toType>& aAnotherType)
{
	myX = static_cast<T>(aAnotherType.myX);
	myY = static_cast<T>(aAnotherType.myY);
}

typedef Vector2<float> Vector2f;