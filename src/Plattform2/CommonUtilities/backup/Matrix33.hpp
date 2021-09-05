#pragma once

#include "Matrix33decl.h"

namespace CommonUtilities
{
	template<class T>
	T& Matrix33<T>::operator()(const int aRow, const int aColumn)
	{
		return myMatrix[((aRow - 1) * 3) + (aColumn - 1)];
	}

	template<class T>
	T Matrix33<T>::operator()(const int aRow, const int aColumn) const
	{
		return myMatrix[((aRow - 1) * 3) + (aColumn-1)];
	}


	template<class T>
	void Matrix33<T>::SetIdentity(Matrix33 &aMatrix)
	{
		aMatrix = Matrix33<T>::Identity();
	}

	template<class T>
	Matrix33<T> Matrix33<T>::Identity()
	{
		return Matrix33();
	}

	template<class T>
	Matrix33<T> Matrix33<T>::operator+(const Matrix33 &aMatrix33) const
	{
		Matrix33 matrix;
		for (int i = 0; i < 9; ++i)
		{
			matrix.myMatrix[i] = myMatrix[i] + aMatrix33.myMatrix[i];
		}

		return matrix;
	}

	template<class T>
	Matrix33<T> Matrix33<T>::operator-(const Matrix33 &aMatrix33) const
	{
		Matrix33 matrix;
		for (int i = 0; i < 9; ++i)
		{
			matrix.myMatrix[i] = myMatrix[i] - aMatrix33.myMatrix[i];
		}

		return matrix;
	}

	template<class T>
	Matrix33<T> Matrix33<T>::Transpose(const Matrix33 &aMatrixToTranspose)
	{
		Matrix33 transposed = aMatrixToTranspose;
		std::swap(transposed.myMatrix[1], transposed.myMatrix[3]);
		std::swap(transposed.myMatrix[2], transposed.myMatrix[6]);
		std::swap(transposed.myMatrix[5], transposed.myMatrix[7]);
		return transposed;
	}

	template<class T>
	Matrix33<T>::Matrix33()
	{
		for (int i = 0; i < 9; ++i)
		{
			if (i == 0 || i == 4 || i == 8)
			{
				myMatrix[i] = 1;
			}
			else
			{
				myMatrix[i] = 0;
			}			
		}
	}

	template<class T>
	Matrix33<T>::Matrix33(const Matrix44<T> &aMatrix)
	{
		myMatrix[0] = aMatrix.myMatrix[0];
		myMatrix[1] = aMatrix.myMatrix[1];
		myMatrix[2] = aMatrix.myMatrix[2];

		myMatrix[3] = aMatrix.myMatrix[4];
		myMatrix[4] = aMatrix.myMatrix[5];
		myMatrix[5] = aMatrix.myMatrix[6];

		myMatrix[6] = aMatrix.myMatrix[8];
		myMatrix[7] = aMatrix.myMatrix[9];
		myMatrix[8] = aMatrix.myMatrix[10];  
	}

	template<class T>
	bool Matrix33<T>::operator==(const Matrix33 &aMatrix) const
	{
		for (int i = 0; i < 9; ++i)
		{
			if (myMatrix[i] != aMatrix.myMatrix[i])
			{
				return false;
			}
		}

		return true;
	}

	template<class T>
	void Matrix33<T>::operator=(const Matrix33 &aMatrix)
	{
		memcpy(&myMatrix, &aMatrix.myMatrix, sizeof(T) * 9);
	}

	template<class T>
	Matrix33<T> Matrix33<T>::operator*(const Matrix33 &aMatrix) const
	{
		Matrix33 matrix;
		matrix.myMatrix[0] = myMatrix[0] * aMatrix.myMatrix[0] + myMatrix[1] * aMatrix.myMatrix[3] + myMatrix[2] * aMatrix.myMatrix[6];
		matrix.myMatrix[1] = myMatrix[0] * aMatrix.myMatrix[1] + myMatrix[1] * aMatrix.myMatrix[4] + myMatrix[2] * aMatrix.myMatrix[7];
		matrix.myMatrix[2] = myMatrix[0] * aMatrix.myMatrix[2] + myMatrix[1] * aMatrix.myMatrix[5] + myMatrix[2] * aMatrix.myMatrix[8];

		matrix.myMatrix[3] = myMatrix[3] * aMatrix.myMatrix[0] + myMatrix[4] * aMatrix.myMatrix[3] + myMatrix[5] * aMatrix.myMatrix[6];
		matrix.myMatrix[4] = myMatrix[3] * aMatrix.myMatrix[1] + myMatrix[4] * aMatrix.myMatrix[4] + myMatrix[5] * aMatrix.myMatrix[7];
		matrix.myMatrix[5] = myMatrix[3] * aMatrix.myMatrix[2] + myMatrix[4] * aMatrix.myMatrix[5] + myMatrix[5] * aMatrix.myMatrix[8];

		matrix.myMatrix[6] = myMatrix[6] * aMatrix.myMatrix[0] + myMatrix[7] * aMatrix.myMatrix[3] + myMatrix[8] * aMatrix.myMatrix[6];
		matrix.myMatrix[7] = myMatrix[6] * aMatrix.myMatrix[1] + myMatrix[7] * aMatrix.myMatrix[4] + myMatrix[8] * aMatrix.myMatrix[7];
		matrix.myMatrix[8] = myMatrix[6] * aMatrix.myMatrix[2] + myMatrix[7] * aMatrix.myMatrix[5] + myMatrix[8] * aMatrix.myMatrix[8];
		
		return matrix;
	}

	template<class T>
	Matrix33<T>& Matrix33<T>::operator*=(const Matrix33& aMatrix)
	{
		*this = *this * aMatrix;
		return *this;
	}

	template<class T>
	Matrix33<T> Matrix33<T>::CreateRotationAroundX(T aAngleInRadians)
	{
		Matrix33 matrix;
		matrix.myMatrix[4] = cos(aAngleInRadians);
		matrix.myMatrix[5] = sin(aAngleInRadians);
		matrix.myMatrix[7] = -sin(aAngleInRadians);
		matrix.myMatrix[8] = cos (aAngleInRadians);

		return matrix;
	}

	template<class T>
	Matrix33<T> Matrix33<T>::CreateRotationAroundY(T aAngleInRadians)
	{
		Matrix33 matrix;
		matrix.myMatrix[0] = cos(aAngleInRadians);
		matrix.myMatrix[2] = -sin(aAngleInRadians);
		matrix.myMatrix[6] = sin(aAngleInRadians);
		matrix.myMatrix[8] = cos(aAngleInRadians);

		return matrix;
	}

	template<class T>
	Matrix33<T> Matrix33<T>::CreateRotationAroundZ(T aAngleInRadians)
	{
		Matrix33 matrix;
		matrix.myMatrix[0] = cos(aAngleInRadians);
		matrix.myMatrix[1] = sin(aAngleInRadians);
		matrix.myMatrix[3] = -sin(aAngleInRadians);
		matrix.myMatrix[4] = cos(aAngleInRadians);

		return matrix;
	}

	template<class T>
	float Matrix33<T>::Determinant() const
	{
		return	myMatrix[0] * (myMatrix[4] * myMatrix[5] - myMatrix[5] * myMatrix[7]) + 
				myMatrix[1] * (myMatrix[5] * myMatrix[6] - myMatrix[3] * myMatrix[8]) +
				myMatrix[2] * (myMatrix[4] * myMatrix[8] - myMatrix[4] * myMatrix[6]);		
	}
}

namespace CU = CommonUtilities;