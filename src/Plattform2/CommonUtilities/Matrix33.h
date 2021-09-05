#pragma once

#include "Matrix33decl.h"

namespace CommonUtilities
{
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
			matrix[i] = myMatrix[i] + aMatrix33.myMatrix[i];
		}

		return matrix;
	}

	template<class T>
	Matrix33<T> Matrix33<T>::operator-(const Matrix33 &aMatrix33) const
	{
		Matrix33 matrix;
		for (int i = 0; i < 9; ++i)
		{
			matrix[i] = myMatrix[i] - aMatrix33.myMatrix[i];
		}

		return matrix;
	}

	template<class T>
	Matrix33<T> Matrix33<T>::Transpose(const Matrix33 &aMatrixToTranspose)
	{
		Matrix33 transposed;
		transposed[1] = aMatrixToTranspose.myMatrix[3];
		transposed[2] = aMatrixToTranspose.myMatrix[6];
		transposed[3] = aMatrixToTranspose.myMatrix[1];
		transposed[5] = aMatrixToTranspose.myMatrix[7];
		transposed[6] = aMatrixToTranspose.myMatrix[2];
		transposed[7] = aMatrixToTranspose.myMatrix[5];

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
			if (myMatrix[i] != aMatrix[myMatrix])
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

	//template<class T>
	//void Matrix33<T>::Matrix33(const Matrix44 &aMatrix)
	//{
	//	for (int i = 0; i < 3; ++i)
	//	{
	//		myMatrix[i] = aMatrix.myMatrix[i];
	//	}
	//	for (int i = 3; i < 6; ++i)
	//	{
	//		myMatrix[i] = aMatrix.myMatrix[i+1];
	//	}
	//	for (int i = 6; i < 9; ++i)
	//	{
	//		myMatrix[i] = aMatrix.myMatrix[i+2];
	//	}
	//}

	template<class T>
	Matrix33<T> Matrix33<T>::operator*(const Matrix33 &aMatrix33) const
	{
		Matrix33 matrix;
		matrix[0] = myMatrix[0] * aMatrix33.myMatrix[0] + myMatrix[1] * aMatrix33.myMatrix[3] + myMatrix[2] * aMatrix33.myMatrix[6];
		matrix[1] = myMatrix[0] * aMatrix33.myMatrix[1] + myMatrix[1] * aMatrix33.myMatrix[4] + myMatrix[2] * aMatrix33.myMatrix[7];
		matrix[2] = myMatrix[0] * aMatrix33.myMatrix[2] + myMatrix[1] * aMatrix33.myMatrix[5] + myMatrix[2] * aMatrix33.myMatrix[8];

		matrix[3] = myMatrix[3] * aMatrix33.myMatrix[0] + myMatrix[4] * aMatrix33.myMatrix[3] + myMatrix[5] * aMatrix33.myMatrix[6];
		matrix[4] = myMatrix[3] * aMatrix33.myMatrix[1] + myMatrix[4] * aMatrix33.myMatrix[4] + myMatrix[5] * aMatrix33.myMatrix[7];
		matrix[5] = myMatrix[3] * aMatrix33.myMatrix[2] + myMatrix[4] * aMatrix33.myMatrix[5] + myMatrix[5] * aMatrix33.myMatrix[8];

		matrix[6] = myMatrix[6] * aMatrix33.myMatrix[0] + myMatrix[7] * aMatrix33.myMatrix[3] + myMatrix[8] * aMatrix33.myMatrix[6];
		matrix[7] = myMatrix[6] * aMatrix33.myMatrix[1] + myMatrix[7] * aMatrix33.myMatrix[4] + myMatrix[8] * aMatrix33.myMatrix[7];
		matrix[8] = myMatrix[6] * aMatrix33.myMatrix[2] + myMatrix[7] * aMatrix33.myMatrix[5] + myMatrix[8] * aMatrix33.myMatrix[8];
		
		return matrix;
	}

	template<class T>
	Matrix33<T> Matrix33<T>::CreateRotateAroundX(T aAngleInRadians)
	{
		Matrix33 matrix;
		matrix[4] = cos(aAngleInRadians);
		matrix[5] = sin(aAngleInRadians);
		matrix[7] = -sin(aAngleInRadians);
		matrix[8] = cos (aAngleInRadians);

		return matrix;
	}

	template<class T>
	Matrix33<T> Matrix33<T>::CreateRotateAroundY(T aAngleInRadians)
	{
		Matrix33 matrix;
		matrix[0] = cos(aAngleInRadians);
		matrix[2] = -sin(aAngleInRadians);
		matrix[6] = sin(aAngleInRadians);
		matrix[8] = cos(aAngleInRadians);

		return matrix;
	}

	template<class T>
	Matrix33<T> Matrix33<T>::CreateRotateAroundZ(T aAngleInRadians)
	{
		Matrix33 matrix;
		matrix[0] = cos(aAngleInRadians);
		matrix[1] = sin(aAngleInRadians);
		matrix[3] = -sin(aAngleInRadians);
		matrix[4] = cos(aAngleInRadians);

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