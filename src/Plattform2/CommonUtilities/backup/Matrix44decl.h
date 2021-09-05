#ifndef MATRIX44DECL_H
#define MATRIX44DECL_H

#include "vector2.h"
#include "Vector3.h"
#ifndef VECTOR4_H
#include "Vector4.h"
#endif
#include "CommonMacros.h"
#include <intrin.h>

template<typename t>
class Vector4;

namespace CommonUtilities
{
	template<class T>
	class DllAPI Matrix44
	{
	public:
								Matrix44();
								Matrix44(T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T);
		Matrix44				operator+(const Matrix44 &aMatrix44) const;
		Matrix44				operator-(const Matrix44 &aMatrix44) const;
		Matrix44				operator*(const Matrix44 &aMatrix44) const;
		Matrix44&				operator*=(const Matrix44 &aMatrix44);

	//	Matrix44				operator*(const Vector4<T> &aVector4) const;
		bool					operator==(const Matrix44 &aMatrix44) const;
		void					operator=(const Matrix44 &aMatrix44);

		Matrix44&				Transpose();
		Matrix44&				Inverse();

		Matrix44				GetInverse() const;

		T&						operator()(const int aRow, const int aColumn);
		T						operator()(const int aRow, const int aColumn) const;

		void					CreateProjectionMatrixLH(T aNearZ, T aFarZ, T aAspectRatio, T aFovAngle);
		void					Translate(const T aX, const T aY, const T aZ);
		void					Translate(const Vector4<T>& aTranslation);
		void					Translate(const Vector3<T>& aTranslation);
		void					Scale(const T aX, const T aY, const T aZ);
		void					SetPosition(const Vector4<T> &aVector4);
		void					SetPosition(const Vector3<T> &aVector3);
		void					SetPosition(const T aX, const T aY, const T aZ, const T aW);
		void					SetHeading(const Vector3<T> &aForward, const Vector3<T> &aUp);
		Vector4<T>				GetPosition() const;
		Vector3<T>				GetPosition3() const;
		// returns vector with X and Z
		Vector2<T>				GetPosition2() const;
		Vector4<T>				GetForward() const;
		// Returns vector with normalized X and Z
		Vector2<T>				GetForward2() const; 
		Vector3<T>				GetForward3() const;		
		Vector4<T>				GetUp() const;
		Vector3<T>				GetUp3() const;
		Vector4<T>				GetRight() const;

		Vector4<T>				GetColumn(const unsigned int aIndex) const;
		Vector3<T>				GetColumn3(const unsigned int aIndex) const;
		Vector4<T>				GetRow(const unsigned int aIndex) const;
		void					SetColumn(const unsigned int aIndex, const Vector4<T> &aVector4);
		void					SetColumn(const unsigned int aIndex, const Vector3<T> &aVector3);
		T&						myX();
		T&						myY();
		T&						myZ();
		/*float					Determinant() const;*/

		void					EulerRotate(const Vector3<T>& someEulerAngles);

		static Matrix44			Transpose(const Matrix44 &aMatrixToTranspose);
		static Matrix44			CreateRotationAroundX(T aAngleInRadians);
		static Matrix44			CreateRotationAroundY(T aAngleInRadians);
		static Matrix44			CreateRotationAroundZ(T aAngleInRadians);
		static Matrix44			GetFastInverse(const Matrix44& aMatrix);
		static const Matrix44&	Identity();

		static void				SetIdentity(Matrix44 &aMatrix);

		//__declspec(align(32))
		union
		{
			__m128					mySSE2Data[4];
			T						myMatrix[16];
			T						myMatx[4][4];
		};

	};

	template<class T>
	Vector4<T> operator* (const Matrix44<T>& aMatrix44, const Vector4<T> &aVector4);

	template<class T>
	Matrix44<T>	Inverse(const Matrix44<T> &aMatrix);
}

namespace CU = CommonUtilities;

#endif