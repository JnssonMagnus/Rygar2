#pragma once

#include "Matrix44decl.h"
#include <algorithm>
#include <iostream>
#include <assert.h>

namespace CommonUtilities
{
#ifdef DLLEXPORT
	template<class T>
	void Matrix44<T>::SetIdentity(Matrix44 &aMatrix)
	{
		aMatrix = Matrix44<T>::Identity();
	}
	
	template<class T>
	T& Matrix44<T>::operator()(const int aRow, const int aColumn)
	{
		return myMatx[aRow-1][aColumn-1];
	}

	template<class T>
	T Matrix44<T>::operator()(const int aRow, const int aColumn) const
	{
		return myMatx[aRow-1][aColumn-1];
	}	

	template<class T>
	const Matrix44<T>& Matrix44<T>::Identity()
	{
		const static Matrix44<T> identityMatrix;
		return identityMatrix;
	}

	template<class T>
	Matrix44<T>& Matrix44<T>::Inverse()
	{
		Vector4<T> translation = GetPosition();
		SetPosition(0, 0, 0, 1);
		translation *= -1;
		translation.w = 1;
		Transpose();
		translation = (*this) * translation;
		SetPosition(translation);
		return *this;
	}	

	template<class T>
	Matrix44<T> Matrix44<T>::GetInverse() const
	{
		Matrix44<T> inversedMatrix = *this;
		inversedMatrix.Inverse();
		return inversedMatrix;
	}

	template<class T>
	Matrix44<T> Matrix44<T>::GetRealInverse() const
	{
		double inv[16], det;
		int i;
		const float (&m)[16] = myMatrix;

		inv[0] = m[5] * m[10] * m[15] -
			m[5] * m[11] * m[14] -
			m[9] * m[6] * m[15] +
			m[9] * m[7] * m[14] +
			m[13] * m[6] * m[11] -
			m[13] * m[7] * m[10];

		inv[4] = -m[4] * m[10] * m[15] +
			m[4] * m[11] * m[14] +
			m[8] * m[6] * m[15] -
			m[8] * m[7] * m[14] -
			m[12] * m[6] * m[11] +
			m[12] * m[7] * m[10];

		inv[8] = m[4] * m[9] * m[15] -
			m[4] * m[11] * m[13] -
			m[8] * m[5] * m[15] +
			m[8] * m[7] * m[13] +
			m[12] * m[5] * m[11] -
			m[12] * m[7] * m[9];

		inv[12] = -m[4] * m[9] * m[14] +
			m[4] * m[10] * m[13] +
			m[8] * m[5] * m[14] -
			m[8] * m[6] * m[13] -
			m[12] * m[5] * m[10] +
			m[12] * m[6] * m[9];

		inv[1] = -m[1] * m[10] * m[15] +
			m[1] * m[11] * m[14] +
			m[9] * m[2] * m[15] -
			m[9] * m[3] * m[14] -
			m[13] * m[2] * m[11] +
			m[13] * m[3] * m[10];

		inv[5] = m[0] * m[10] * m[15] -
			m[0] * m[11] * m[14] -
			m[8] * m[2] * m[15] +
			m[8] * m[3] * m[14] +
			m[12] * m[2] * m[11] -
			m[12] * m[3] * m[10];

		inv[9] = -m[0] * m[9] * m[15] +
			m[0] * m[11] * m[13] +
			m[8] * m[1] * m[15] -
			m[8] * m[3] * m[13] -
			m[12] * m[1] * m[11] +
			m[12] * m[3] * m[9];

		inv[13] = m[0] * m[9] * m[14] -
			m[0] * m[10] * m[13] -
			m[8] * m[1] * m[14] +
			m[8] * m[2] * m[13] +
			m[12] * m[1] * m[10] -
			m[12] * m[2] * m[9];

		inv[2] = m[1] * m[6] * m[15] -
			m[1] * m[7] * m[14] -
			m[5] * m[2] * m[15] +
			m[5] * m[3] * m[14] +
			m[13] * m[2] * m[7] -
			m[13] * m[3] * m[6];

		inv[6] = -m[0] * m[6] * m[15] +
			m[0] * m[7] * m[14] +
			m[4] * m[2] * m[15] -
			m[4] * m[3] * m[14] -
			m[12] * m[2] * m[7] +
			m[12] * m[3] * m[6];

		inv[10] = m[0] * m[5] * m[15] -
			m[0] * m[7] * m[13] -
			m[4] * m[1] * m[15] +
			m[4] * m[3] * m[13] +
			m[12] * m[1] * m[7] -
			m[12] * m[3] * m[5];

		inv[14] = -m[0] * m[5] * m[14] +
			m[0] * m[6] * m[13] +
			m[4] * m[1] * m[14] -
			m[4] * m[2] * m[13] -
			m[12] * m[1] * m[6] +
			m[12] * m[2] * m[5];

		inv[3] = -m[1] * m[6] * m[11] +
			m[1] * m[7] * m[10] +
			m[5] * m[2] * m[11] -
			m[5] * m[3] * m[10] -
			m[9] * m[2] * m[7] +
			m[9] * m[3] * m[6];

		inv[7] = m[0] * m[6] * m[11] -
			m[0] * m[7] * m[10] -
			m[4] * m[2] * m[11] +
			m[4] * m[3] * m[10] +
			m[8] * m[2] * m[7] -
			m[8] * m[3] * m[6];

		inv[11] = -m[0] * m[5] * m[11] +
			m[0] * m[7] * m[9] +
			m[4] * m[1] * m[11] -
			m[4] * m[3] * m[9] -
			m[8] * m[1] * m[7] +
			m[8] * m[3] * m[5];

		inv[15] = m[0] * m[5] * m[10] -
			m[0] * m[6] * m[9] -
			m[4] * m[1] * m[10] +
			m[4] * m[2] * m[9] +
			m[8] * m[1] * m[6] -
			m[8] * m[2] * m[5];

		det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

		Matrix44 invOut;

		if (det != 0)
		{
			det = 1.0 / det;

			for (i = 0; i < 16; i++)
				invOut.myMatrix[i] = inv[i] * det;
		}
		else
		{
			assert(false && "determinant is zero!");
		}
		return invOut;
	}


	template<class T>
	Matrix44<T> Matrix44<T>::operator+(const Matrix44& aMatrix44) const
	{
		Matrix44 matrix;
		for (int i = 0; i < 16; ++i)
		{
			matrix.myMatrix[i] = myMatrix[i] + aMatrix44.myMatrix[i];
		}

		return matrix;
	}

	template<class T>
	Matrix44<T> Matrix44<T>::operator-(const Matrix44& aMatrix44) const
	{
		Matrix44 matrix;
		for (int i = 0; i < 16; ++i)
		{
			matrix.myMatrix[i] = myMatrix[i] - aMatrix44.myMatrix[i];
		}

		return matrix;
	}

	template<class T>
	Matrix44<T>& Matrix44<T>::Transpose()
	{
		std::swap(myMatrix[1], myMatrix[4]);
		std::swap(myMatrix[2], myMatrix[8]);
		std::swap(myMatrix[3], myMatrix[12]);
		std::swap(myMatrix[6], myMatrix[9]);
		std::swap(myMatrix[7], myMatrix[13]);
		std::swap(myMatrix[11], myMatrix[14]);

		return *this;
	}

	template<class T>
	Matrix44<T> Matrix44<T>::Transpose(const Matrix44 &aMatrixToTranspose)
	{
		Matrix44 transposed;
		transposed.myMatrix[0] = aMatrixToTranspose.myMatrix[0];
		transposed.myMatrix[1] = aMatrixToTranspose.myMatrix[4];
		transposed.myMatrix[2] = aMatrixToTranspose.myMatrix[8];
		transposed.myMatrix[3] = aMatrixToTranspose.myMatrix[12];

		transposed.myMatrix[4] = aMatrixToTranspose.myMatrix[1];
		transposed.myMatrix[5] = aMatrixToTranspose.myMatrix[5];
		transposed.myMatrix[6] = aMatrixToTranspose.myMatrix[9];
		transposed.myMatrix[7] = aMatrixToTranspose.myMatrix[13];

		transposed.myMatrix[8] = aMatrixToTranspose.myMatrix[2];
		transposed.myMatrix[9] = aMatrixToTranspose.myMatrix[6];
		transposed.myMatrix[10] = aMatrixToTranspose.myMatrix[10];
		transposed.myMatrix[11] = aMatrixToTranspose.myMatrix[14];

		transposed.myMatrix[12] = aMatrixToTranspose.myMatrix[3];
		transposed.myMatrix[13] = aMatrixToTranspose.myMatrix[7];
		transposed.myMatrix[14] = aMatrixToTranspose.myMatrix[11];
		transposed.myMatrix[15] = aMatrixToTranspose.myMatrix[15];

		return transposed;
	}

	template<class T>
	Matrix44<T>::Matrix44() 
	{
		myMatrix[0] = 1.f; myMatrix[1] = 0.f; myMatrix[2] = 0.f; myMatrix[3] = 0.f;
		myMatrix[4] = 0.f; myMatrix[5] = 1.f; myMatrix[6] = 0.f; myMatrix[7] = 0.f;
		myMatrix[8] = 0.f; myMatrix[9] = 0.f; myMatrix[10] = 1.f; myMatrix[11] = 0.f;
		myMatrix[12] = 0.f; myMatrix[13] = 0.f; myMatrix[14] = 0.f; myMatrix[15] = 1.f;
	}

	template<class T>
	Matrix44<T>::Matrix44(	float aRightX, float aRightY, float aRightZ, float aRightW, 
							float aUpX, float aUpY, float aUpZ, float aUpW,
							float aForwardX, float aForwardY, float aForwardZ, float aForwardW,
							float aPosX, float aPosY, float aPosZ, float aPosW) 
	{
		myMatrix[0] = aRightX;
		myMatrix[4] = aRightY;
		myMatrix[8] = aRightZ;
		myMatrix[12] = aRightW;

		myMatrix[1] = aUpX;
		myMatrix[5] = aUpY;
		myMatrix[9] = aUpZ;
		myMatrix[13] = aUpW;

		myMatrix[2] = aForwardX;
		myMatrix[6] = aForwardY;
		myMatrix[10] = aForwardZ;
		myMatrix[14] = aForwardW;

		myMatrix[3] = aPosX;
		myMatrix[7] = aPosY;
		myMatrix[11] = aPosZ;
		myMatrix[15] = aPosW;
	}

	template<class T>
	T& Matrix44<T>::myX()
	{
		return myMatrix[3];
	}

	template<class T>
	T& Matrix44<T>::myY()
	{
		return myMatrix[7];
	}

	template<class T>
	T& Matrix44<T>::myZ()
	{
		return myMatrix[11];
	}


	template<class T>
	bool Matrix44<T>::operator==(const Matrix44 &aMatrix) const
	{
		for (int i = 0; i < 15; ++i)
		{
			if (myMatrix[i] != aMatrix.myMatrix[i])
			{
				return false;
			}
		}

		return true;
	}

	template<class T>
	void Matrix44<T>::operator=(const Matrix44 &aMatrix)
	{
		memcpy(&myMatrix, &aMatrix.myMatrix, sizeof(T) * 16);
	}
	
	template<class T>
	Matrix44<T> Matrix44<T>::operator*(const Matrix44 &aMatrix) const
	{
		Matrix44 matrix;

		for (unsigned int i = 0; i < 4; ++i)
		{
			for (unsigned int j = 0; j < 4; ++j)
			{
				__m128 data = _mm_setr_ps(aMatrix.myMatrix[0 + j], aMatrix.myMatrix[4 + j], aMatrix.myMatrix[8 + j], aMatrix.myMatrix[12 + j]);
				matrix.myMatrix[i * 4 + j] = _mm_dp_ps(mySSE2Data[i], data, 0xff).m128_f32[0];
			}
		}

		return matrix;
	}

	template<class T>
	Matrix44<T>& Matrix44<T>::operator*=(const Matrix44 &aMatrix44)
	{
		(*this) = (*this) * aMatrix44;

		return (*this);
	}

	template<class T>
	Matrix44<T> Matrix44<T>::CreateRotationAroundX(T aAngleInRadians)
	{
		Matrix44 matrix;
		matrix.myMatrix[5] = cos(aAngleInRadians);
		matrix.myMatrix[6] = sin(aAngleInRadians);
		matrix.myMatrix[9] = -sin(aAngleInRadians);
		matrix.myMatrix[10] = cos (aAngleInRadians);

		return matrix;
	}

	template<class T>
	Matrix44<T> Matrix44<T>::CreateRotationAroundY(T aAngleInRadians)
	{
		Matrix44 matrix;
		matrix.myMatrix[0] = cos(aAngleInRadians);
		matrix.myMatrix[2] = -sin(aAngleInRadians);
		matrix.myMatrix[8] = sin(aAngleInRadians);
		matrix.myMatrix[10] = cos(aAngleInRadians);

		return matrix;
	}

	template<class T>
	Matrix44<T> Matrix44<T>::CreateRotationAroundZ(T aAngleInRadians)
	{
		Matrix44 matrix;
		matrix.myMatrix[0] = cos(aAngleInRadians);
		matrix.myMatrix[1] = sin(aAngleInRadians);
		matrix.myMatrix[4] = -sin(aAngleInRadians);
		matrix.myMatrix[5] = cos(aAngleInRadians);

		return matrix;
	}

	template<class T>
	void Matrix44<T>::Translate(const float aX, const float aY, const float aZ)
	{
		Matrix44 matrix;
		matrix.myMatrix[3] = aX;
		matrix.myMatrix[7] = aY;
		matrix.myMatrix[11] = aZ;

		*this *= matrix;
	}

	template<class T>
	void Matrix44<T>::Translate(const Vector3<float>& aTranslation)
	{
		Translate(aTranslation.myX, aTranslation.myY, aTranslation.myZ);
	}

	template<class T>
	void Matrix44<T>::Translate(const Vector4<float>& aTranslation)
	{
		Translate(aTranslation.myX, aTranslation.myY, aTranslation.myZ);
	}


	template<class T>
	void Matrix44<T>::Scale(const float aX, const float aY, const float aZ)
	{
		Matrix44 matrix;
		matrix.myMatrix[0] = aX;
		matrix.myMatrix[5] = aY;
		matrix.myMatrix[10] = aZ;

		*this *= matrix;
	}

	template<class T>
	void Matrix44<T>::SetPosition(const Vector4<T> &aVector4)
	{
		SetPosition(aVector4.myX, aVector4.myY, aVector4.myZ, aVector4.myW);
	}

	template<class T>
	void Matrix44<T>::SetPosition(const Vector3<T> &aVector3)
	{
		SetPosition(aVector3.myX, aVector3.myY, aVector3.myZ, 1.f);
	}


	template<class T>
	void Matrix44<T>::SetPosition(const T aX, const T aY, const T aZ, const T aW)
	{
		myMatrix[3] = aX;
		myMatrix[7] = aY;
		myMatrix[11] = aZ;
		myMatrix[15] = aW;
	}

	template<class T>
	Vector4<T> Matrix44<T>::GetPosition() const
	{
		return Vector4<T>(myMatrix[3], myMatrix[7], myMatrix[11], myMatrix[15]);
	}

	template<class T>
	Vector3<T> Matrix44<T>::GetPosition3() const
	{
		return Vector3<T>(myMatrix[3], myMatrix[7], myMatrix[11]);
	}

	template<class T>
	Vector2<T> Matrix44<T>::GetPosition2() const
	{
		return Vector2<T>(myMatrix[3], myMatrix[7]);
	}

	template<class T>
	Vector4<T> operator* (const Matrix44<T>& aMatrix4, const Vector4<T> &aVector4)
	{
		Vector4<T> result;
		result.myX = aVector4.Dot( *(reinterpret_cast<const Vector4<T>*>(&aMatrix4.myMatrix[0])));
		result.myY = aVector4.Dot( *(reinterpret_cast<const Vector4<T>*>(&aMatrix4.myMatrix[4])));
		result.myZ = aVector4.Dot( *(reinterpret_cast<const Vector4<T>*>(&aMatrix4.myMatrix[8])));
		result.myW = aVector4.Dot( *(reinterpret_cast<const Vector4<T>*>(&aMatrix4.myMatrix[12])));

		return result;
	}

	template<class T>
	Matrix44<T>	Inverse(const Matrix44<T> &aMatrix)
	{
		Matrix44<T> matrix = aMatrix;
		matrix.Inverse();
		return matrix;
	}

	template<class T>
	Vector4<T> Matrix44<T>::GetForward() const
	{
		return GetColumn(2);
	}

	template<class T>
	Vector3<T> Matrix44<T>::GetForward3() const
	{
		return GetColumn3(2);
	}

	template<class T>
	Vector2<T> Matrix44<T>::GetForward2() const
	{
		Vector2<T> forward2(myMatrix[2], myMatrix[2 + 8]);
		forward2.Normalize();
		return forward2;
	}

	template<class T>
	Vector4<T> Matrix44<T>::GetUp() const
	{
		return GetColumn(1);
	}

	template<class T>
	Vector3<T> Matrix44<T>::GetUp3() const
	{
		return GetColumn3(1);
	}

	template<class T>
	Vector4<T> Matrix44<T>::GetRight() const
	{
		return GetColumn(0);
	}


	template<class T>
	Vector4<T> Matrix44<T>::GetColumn(const unsigned int aIndex) const
	{
		return Vector4<T>(myMatrix[aIndex], myMatrix[aIndex+4], myMatrix[aIndex+8], myMatrix[aIndex+12]);
	}

	template<class T>
	Vector3<T> Matrix44<T>::GetColumn3(const unsigned int aIndex) const
	{
		return Vector3<T>(myMatrix[aIndex], myMatrix[aIndex + 4], myMatrix[aIndex + 8]);
	}

	template<class T>
	Vector4<T> Matrix44<T>::GetRow(const unsigned int aIndex) const
	{
		return Vector4<T>(myMatrix[aIndex], myMatrix[aIndex+1], myMatrix[aIndex+2], myMatrix[aIndex+3]);
	}

	template<class T>
	void Matrix44<T>::CreateProjectionMatrixLH(T aNearZ, T aFarZ, T aAspectRatio,T aFovAngle)
	{
		T sinFov;
		T cosFov;
		T height;
		T width;

		sinFov = sin(0.5f * aFovAngle);
		cosFov = cos(0.5f * aFovAngle);
	
		height = cosFov / sinFov;
		width = height / aAspectRatio;

		T scaling = aFarZ / (aFarZ - aNearZ);

		myMatrix[0] = width;
		myMatrix[5] = height;
		myMatrix[10] = scaling;
		myMatrix[11] = -scaling * aNearZ;
		myMatrix[14] = 1.0f;
		myMatrix[15] = 0.f;
	}

	template<class T>
	Vector4<T> GetScreenPosition(const CU::Matrix44<T> &aMatrix, const CU::Matrix44<T> &aCamera, const CU::Matrix44<T> &aProjection, const float aScreenWidth, const float aScreenHeight)
	{
		CU::Matrix44<T> cameraInverse = CU::Inverse(aCamera);
		Vector4<T> cameraSpace = cameraInverse * aMatrix.GetPosition(); // move to camera space

		Vector4<T> screenSpace = aProjection * cameraSpace;
		if (screenSpace.myW >= 0)
		{
			screenSpace.myX /= screenSpace.myW;
			screenSpace.myY /= screenSpace.myW;
			screenSpace.myZ /= screenSpace.myW;
		}
		else
		{
			screenSpace.myX /= -screenSpace.myW;
			screenSpace.myY /= -screenSpace.myW;
			screenSpace.myZ /= -screenSpace.myW;
		}

		screenSpace.myY *= -1;

		screenSpace.x /= 2.f;
		screenSpace.y /= 2.f;
		screenSpace.x += 0.5f;
		screenSpace.y += 0.5f;
		screenSpace.x *= aScreenWidth;
		screenSpace.y *= aScreenHeight;
	
		return screenSpace;
	}

	template<class T>
	void Matrix44<T>::SetHeading(const Vector3<float> &aNormalizedForward, const Vector3<float> &aNormalizedUp)
	{
		Vector3<float> right = aNormalizedUp.Cross(aNormalizedForward);
		SetColumn(0, right);
		SetColumn(1, aNormalizedUp);
		SetColumn(2, aNormalizedForward);
	}

	template<class T>
	void Matrix44<T>::SetColumn(const unsigned int aIndex, const Vector4<float> &aVector4)
	{
		myMatrix[aIndex] = aVector4.myX;
		myMatrix[aIndex + 4] = aVector4.myY;
		myMatrix[aIndex + 8] = aVector4.myZ;
	}

	template<class T>
	void Matrix44<T>::SetColumn(const unsigned int aIndex, const Vector3<float> &aVector3)
	{
		myMatrix[aIndex] = aVector3.myX;
		myMatrix[aIndex + 4] = aVector3.myY;
		myMatrix[aIndex + 8] = aVector3.myZ;
	}

	template<class T>
	void Matrix44<T>::EulerRotate(const Vector3<T>& someEulerAngles)
	{
		const Vector3<T> position = GetPosition3();
		*this = CU::Matrix44::Identity();
		*this *= CreateRotationAroundX(someEulerAngles.myX);
		*this *= CreateRotationAroundY(someEulerAngles.myY);
		*this *= CreateRotationAroundZ(someEulerAngles.myZ);
		SetPosition(position);
	}

	template<class T>
	Vector4<T> GetScreenPosition(const Vector4<T> &aVector4, const CU::Matrix44<T> &aCamera, const CU::Matrix44<T> &aProjection)
	{
		CU::Matrix44<T> matrix;
		matrix.Translate(aVector4.myX, aVector4.myY, aVector4.myZ);
		return GetScreenPosition<T>(matrix, aCamera, aProjection);
	}


	//template<class T>
	//float Matrix44<T>::Determinant() const
	//{
	//	return	myMatrix[0] * (myMatrix[4] * myMatrix[5] - myMatrix[5] * myMatrix[7]) + 
	//			myMatrix[1] * (myMatrix[5] * myMatrix[6] - myMatrix[3] * myMatrix[8]) +
	//			myMatrix[2] * (myMatrix[4] * myMatrix[8] - myMatrix[4] * myMatrix[6]);		
	//}
#endif
	typedef Matrix44<float> Matrix44f;

}

template<class T>
std::ostream& operator<< (std::ostream& out, const CommonUtilities::Matrix44<T>& aMatrix)
{
	out << aMatrix.myMatrix[0] << "\t" << aMatrix.myMatrix[1] << "\t" << aMatrix.myMatrix[2] << "\t" << aMatrix.myMatrix[3] << "\t" << std::endl;
	out << aMatrix.myMatrix[4] << "\t" << aMatrix.myMatrix[5] << "\t" << aMatrix.myMatrix[6] << "\t" << aMatrix.myMatrix[7] << "\t" << std::endl;
	out << aMatrix.myMatrix[8] << "\t" << aMatrix.myMatrix[9] << "\t" << aMatrix.myMatrix[10] << "\t" << aMatrix.myMatrix[11] << "\t" << std::endl;
	out << aMatrix.myMatrix[12] << "\t" << aMatrix.myMatrix[13] << "\t" << aMatrix.myMatrix[14] << "\t" << aMatrix.myMatrix[15] << "\t" << std::endl;
	return out;
}

namespace CU = CommonUtilities;