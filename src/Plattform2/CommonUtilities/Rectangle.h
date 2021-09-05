#pragma once
#include "Vector2.h"

namespace Shape
{
	template<class T>
	class Rectangle
	{
	public:
		Rectangle();
		inline const Vector2<T>& GetSrcSize() const;
		inline const Vector2<T>& GetSrcPosition() const;
		inline void SetSrcSize(const T aX, const T aY);
		inline void SetSrcPosition(const T aX, const T aY);

	private:
		Vector2<T> mySrcSize;
		Vector2<T> mySrcPosition;
	};

	template<class T>
	Rectangle<T>::Rectangle()
	{
	}

	template<class T>
	const Vector2<T>& Rectangle<T>::GetSrcSize() const
	{
		return mySrcSize;
	}

	template<class T>
	const Vector2<T>& Rectangle<T>::GetSrcPosition() const
	{
		return mySrcPosition;
	}

	template<class T>
	void Rectangle<T>::SetSrcPosition(const T aX, const T aY)
	{
		mySrcPosition.myX = aX;
		mySrcPosition.myY = aY;
	}

	template<class T>
	void Rectangle<T>::SetSrcSize(const T aX, const T aY)
	{
		mySrcSize.myX = aX;
		mySrcSize.myY = aY;
	}
}