#include "Vector2.h"

Matrix3::Matrix3()
{
	Identity();
}

Matrix3::Matrix3(float _m11, float _m12, float _m13,
			float _m21, float _m22, float _m23,
			float _m31, float _m32, float _m33)
{
	m11 = _m11;
	m12 = _m12;
	m13 = _m13;
	m21 = _m21;
	m22 = _m22;
	m23 = _m23;
	m31 = _m31;
	m32 = _m32;
	m33 = _m33;
}

Vector2 operator*(const Matrix3 &matrix, const Vector2 &vector)
{
	return Vector2(matrix.m11*vector.x + matrix.m12*vector.y,
						matrix.m21*vector.x + matrix.m22*vector.y);
}

Vector2 operator*(const Vector2 &vector, const Matrix3 &matrix)
{
	return Vector2(matrix.m11*vector.x + matrix.m12*vector.y,
						matrix.m21*vector.x + matrix.m22*vector.y);
}

Matrix3 operator*(const Matrix3 &matrix1, const Matrix3 &matrix2)
{
	
	return Matrix3(matrix1.m11*matrix2.m11 + matrix1.m12*matrix2.m21 + matrix1.m13*matrix2.m31,
					matrix1.m11*matrix2.m12 + matrix1.m12*matrix2.m22 + matrix1.m13*matrix2.m32,
					matrix1.m11*matrix2.m13 + matrix1.m12*matrix2.m23 + matrix1.m13*matrix2.m33,

					matrix1.m21*matrix2.m11 + matrix1.m22*matrix2.m21 + matrix1.m23*matrix2.m31,
					matrix1.m21*matrix2.m12 + matrix1.m22*matrix2.m22 + matrix1.m23*matrix2.m32,
					matrix1.m21*matrix2.m13 + matrix1.m22*matrix2.m23 + matrix1.m23*matrix2.m33,

					matrix1.m31*matrix2.m11 + matrix1.m32*matrix2.m21 + matrix1.m33*matrix2.m31,
					matrix1.m31*matrix2.m12 + matrix1.m32*matrix2.m22 + matrix1.m33*matrix2.m32,
					matrix1.m31*matrix2.m13 + matrix1.m32*matrix2.m23 + matrix1.m33*matrix2.m33);
}
Matrix3 operator+(const Matrix3 &matrix1, const Matrix3 &matrix2)
{
	return Matrix3(matrix1.m11+matrix2.m11,
					matrix1.m12+matrix2.m12,
					matrix1.m13+matrix2.m13,
					matrix1.m21+matrix2.m21,
					matrix1.m22+matrix2.m22,
					matrix1.m23+matrix2.m23,
					matrix1.m31+matrix2.m31,
					matrix1.m32+matrix2.m32,
					matrix1.m33+matrix2.m33);
					
}

Matrix3 operator-(const Matrix3 &matrix1, const Matrix3 &matrix2)
{
	return Matrix3(matrix1.m11-matrix2.m11,
					matrix1.m12-matrix2.m12,
					matrix1.m13-matrix2.m13,
					matrix1.m21-matrix2.m21,
					matrix1.m22-matrix2.m22,
					matrix1.m23-matrix2.m23,
					matrix1.m31-matrix2.m31,
					matrix1.m32-matrix2.m32,
					matrix1.m33-matrix2.m33);
					
}


Matrix3& Matrix3::operator*=(const Matrix3 &matrix)
{
	(*this)*matrix;
	return (*this);
}

Matrix3& Matrix3::operator+=(const Matrix3 &matrix)
{
	m11 += matrix.m11;
	m12 += matrix.m12;
	m13 += matrix.m13;
	m21 += matrix.m21;
	m22 += matrix.m22;
	m23 += matrix.m23;
	m31 += matrix.m31;
	m32 += matrix.m32;
	m33 += matrix.m33;

	return (*this);
}

Matrix3& Matrix3::operator-=(const Matrix3 &matrix)
{
	m11 -= matrix.m11;
	m12 -= matrix.m12;
	m13 -= matrix.m13;
	m21 -= matrix.m21;
	m22 -= matrix.m22;
	m23 -= matrix.m23;
	m31 -= matrix.m31;
	m32 -= matrix.m32;
	m33 -= matrix.m33;

	return (*this);
}

Matrix3& Matrix3::operator/=(float value)
{
	m11 /= value;
	m12 /= value;
	m13 /= value;
	m21 /= value;
	m22 /= value;
	m23 /= value;
	m31 /= value;
	m32 /= value;
	m33 /= value;

	return (*this);
}


Matrix3& Matrix3::operator*=(float value)
{
	m11 *= value;
	m12 *= value;
	m13 *= value;
	m21 *= value;
	m22 *= value;
	m23 *= value;
	m31 *= value;
	m32 *= value;
	m33 *= value;

	return (*this);
}

void Matrix3::Identity()
{
	m11 = 1.f; m12 = 0.f; m13 = 0.f;
	m21 = 0.f; m22 = 1.f; m23 = 0.f;
	m31 = 0.f; m32 = 0.f; m33 = 1.f;
}

Matrix3& Matrix3::Transpose()
{
	Matrix3 temp(*this);
	m11 = temp.m11;
	m12 = temp.m21;
	m13 = temp.m31;
	m21 = temp.m12;
	m22 = temp.m22;
	m23 = temp.m32;
	m31 = temp.m13;
	m32 = temp.m23;
	m33 = temp.m33;

	return (*this);
}

void Matrix3::Invert()
{
	float fDeterminant = m11 * (m22*m33 - m32*m23) +
						m21 * (m32*m13 - m12*m33) + 
						m31 * (m12*m23 - m22*m13);

	Matrix3 newMatrix;

	//make sure the determinant is not zero
	if (fabs(fDeterminant) <= 0.00000001f)
		return;

	float fOneOverDet = 1.f/fDeterminant;

	//calculate the 3x3 portion of the inverse
	newMatrix.m11 = (m22*m33 - m23*m32) * fOneOverDet;
	newMatrix.m12 = -(m12*m33 - m13*m32) * fOneOverDet;
	newMatrix.m13 = (m12*m23 - m13*m22) * fOneOverDet;

	newMatrix.m21 = -(m21*m33 - m23*m31) * fOneOverDet;
	newMatrix.m22 = (m11*m33 - m13*m31) * fOneOverDet;
	newMatrix.m23 = -(m11*m23 - m13*m21) * fOneOverDet;

	newMatrix.m31 = (m21*m32 - m22*m31) * fOneOverDet;
	newMatrix.m32 = -(m11*m32 - m12*m31) * fOneOverDet;
	newMatrix.m33 = (m11*m22 - m12*m21) * fOneOverDet;


	*this = newMatrix;
}

void Matrix3::SetRotation(float fRadians)
{
	m[0][0] = cos(fRadians); 
	m[0][1] = sin(fRadians);
	m[1][0] = -sin(fRadians);
	m[1][1] = cos(fRadians);
}
void Matrix3::SetTranslation(const Vector2 &vTranslation)
{
	m[2][0] = vTranslation.x;
	m[2][1] = vTranslation.y;
}

void Matrix3::SetScale(float fScale)
{
	m[0][0] = fScale;
	m[1][1] = fScale;
}

//returns heading, pitch, bank
//void Matrix3::GetEulerAngles(Vector2 &vReturnEuler)const
//{
//	//extract pitch from m23
//	float sp = -m23;
//	if (sp <= -1.f)
//		vReturnEuler.Y = -1.570796f; // -pi/2
//	else if (sp >= 1.f)
//		vReturnEuler.Y = 1.570796f; // pi/2
//	else
//		vReturnEuler.Y = asinf(sp);
//
//	//check for gimbal lock, giving some tolerance for floating error
//	if (sp > 0.9999f)
//	{
//		//set bank to zero
//		vReturnEuler.Z = 0.f;
//		//set the heading
//		vReturnEuler.X = atan2(-m31,m11);		
//	}
//	else
//	{
//		//compute heading
//		vReturnEuler.X = atan2(m13,m33);	
//		//compute bank
//		vReturnEuler.Z = atan2(m21,m22);
//	}
//
//}