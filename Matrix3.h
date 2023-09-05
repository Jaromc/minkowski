#include "Vector2.h"

class Matrix3
{
public:
	union{
	struct{
	float m11, m12, m13;
	float m21, m22, m23;
	float m31, m32, m33;};
	float m[3][3];
};

public:
	Matrix3();
	Matrix3(float _m11, float _m12, float _m13,
			float _m21, float _m22, float _m23,
			float _m31, float _m32, float _m33);

	//transforms a vector by the rotation matrix
	friend Vector2 operator*(const Matrix3 &matrix, const Vector2 &vector);
	friend Vector2 operator*(const Vector2 &vector, const Matrix3 &matrix);
	friend Matrix3 operator*(const Matrix3 &matrix1, const Matrix3 &matrix2);
	friend Matrix3 operator+(const Matrix3 &matrix1, const Matrix3 &matrix2);
	friend Matrix3 operator-(const Matrix3 &matrix1, const Matrix3 &matrix2);
	Matrix3& operator*=(const Matrix3 &matrix);
	Matrix3& operator+=(const Matrix3 &matrix);
	Matrix3& operator-=(const Matrix3 &matrix);
	Matrix3& operator/=(float value);
	Matrix3& operator*=(float value);
	//inverts this rotation matrix
	Matrix3& Transpose();
	//set the matrix to the identity matrix
	void Identity();
	//Inverts this matrix
	void Invert();
	//set rotation in radians
	void SetRotation(float fRadians);
	//sets the translation
	void SetTranslation(const Vector2 &vTranslation);
	//set the scale
	void SetScale(float fScale);

	//returns heading, pitch, bank
	void GetEulerAngles(Vector2 &vReturnEuler)const;
};