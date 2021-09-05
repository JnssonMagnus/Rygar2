#pragma once

#include "vector3.h"
#include "vector4.h"

namespace CommonUtilities
{
	template<class T>
	class Matrix33
	{
	public:
								Matrix33();
								Matrix33(const Matrix44<T> &aMatrix);
		Matrix33				operator+(const Matrix33 &aMatrix33) const;
		Matrix33				operator-(const Matrix33 &aMatrix33) const;
		Matrix33				operator*(const Matrix33 &aMatrix33) const;
		Matrix33&				operator*=(const Matrix33& aMatrix33);

		Matrix33				operator*(const Vector3<T> &aVector3) const;
		bool					operator==(const Matrix33 &aMatrix33) const;
		void					operator=(const Matrix33 &aMatrix33);

		Matrix33				Inverse() const;
		float					Determinant() const;

		T&						operator()(const int aRow, const int aColumn);
		T						operator()(const int aRow, const int aColumn) const;

		static Matrix33			Transpose(const Matrix33 &aMatrixToTranspose);
		static Matrix33			CreateRotationAroundX(T aAngleInRadians);
		static Matrix33			CreateRotationAroundY(T aAngleInRadians);
		static Matrix33			CreateRotationAroundZ(T aAngleInRadians);
		static Matrix33			Identity();


		static void				SetIdentity(Matrix33 &aMatrix);
		T						myMatrix[9];

	};
}

namespace CU = CommonUtilities;