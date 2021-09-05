#pragma once
#include "Vector3.h"

namespace CommonUtilities
{
	template<class T>
	class Line
	{
	protected:
		Vector3<T>	myStartPoint, myEndPoint;
	public:
							Line();
							Line(Vector3<T> aFirstPoint, Vector3<T> aSecondPoint);
							Line(T x1, T y1, T x2, T y2);
		void				InitWith2Points(Vector3<T> aFirstPoint, Vector3<T> aSecondPoint);
		bool				Intersects(Vector3<T> aPosition, float aRadius);
		Vector3<T>			GetStartPoint() const;
		Vector3<T>			GetEndPoint() const;
		void				SetStartPoint(const Vector3<float> aPoint);
		void				SetStartPoint(const T aX, const T aY, const T aZ);
		void				SetEndPoint(const Vector3<float> aPoint);
		void				SetEndPoint(const T aX, const T aY, const T aZ);
		void				RecalculateNormal();
		void				Extend(float aPoints);

		float		myWidth;
		Vector3<T>  myNormal;
	};


	template <class T>
	void Line<T>::Extend(float aPoints)
	{
		Vector3<float> v = myStartPoint - myEndPoint;
		v.Normalize();
		myStartPoint += v * aPoints;
		myEndPoint -= v * aPoints;
	}

	template<class T>
	void Line<T>::SetStartPoint(const Vector3<float> aPoint)
	{
		myStartPoint = aPoint;
		RecalculateNormal();
	}

	template<class T>
	void Line<T>::SetStartPoint(const T aX, const T aY, const T aZ) 
	{
		myStartPoint.myX = aX;
		myStartPoint.myY = aY;
		myStartPoint.myZ = aZ;
		RecalculateNormal();
	}

	template<class T>
	void Line<T>::SetEndPoint(const Vector3<float> aPoint)
	{
		myEndPoint = aPoint;
		RecalculateNormal();
	}

	template<class T>
	void Line<T>::SetEndPoint(const T aX, const T aY, const T aZ)
	{
		myEndPoint.myX = aX;
		myEndPoint.myY = aY;
		myEndPoint.myZ = aZ;
		RecalculateNormal();
	}


	template<class T>
	void Line<T>::RecalculateNormal()
	{
		myNormal = myStartPoint - myEndPoint;
		myNormal.Normalize();
		T temp = myNormal.myX;
		myNormal.myX = myNormal.myY;
		myNormal.myY = -temp;
	}

	template<class T>
	Vector3<T> Line<T>::GetStartPoint() const
	 {
		return myStartPoint;
	}

	template<class T>
	Vector3<T> Line<T>::GetEndPoint() const 
	{
		return myEndPoint;
	}

	template<class T>
	Line<T>::Line() : myWidth(0)
	{
		RecalculateNormal();
	}

	template<class T>
	Line<T>::Line(T x1, T y1, T x2, T y2) : myWidth(1), myStartPoint(x1, y1), myEndPoint(x2, y2)
	{
		RecalculateNormal();
	}

	template<class T>
	Line<T>::Line(Vector3<T> aStartPoint, Vector3<T> aEndPoint) : myWidth(0), myStartPoint(aStartPoint), myEndPoint(aEndPoint)
	{
		RecalculateNormal();
	}

	template<class T>
	bool Line<T>::Intersects(Vector3<T> aPosition, float aRadius)
	{
		Vector3<T> line = myEndPoint - myStartPoint;
		Vector3<T> proj = aPosition - myStartPoint;
		float t = proj.Dot(line) / line.Dot(line);

		// Clamp f
		if (t > 1.f)
			t = 1.f;
		else if (t < 0)
			t = 0;

		Vector3<T> closest = myStartPoint + line * t;
		Vector3<T> dist = closest - aPosition;

		return dist.Length() <= aRadius;
	}

}

namespace CU = CommonUtilities;