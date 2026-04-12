#include "Matrix.h"
#include "../Vector/SIMD/SIMDVectorMath.h"

// 単位行列
Matrix4x4 Matrix4x4::Identity()
{
	return Matrix4x4{
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
}

// 加算
Matrix4x4 Matrix4x4::operator+(const Matrix4x4& _other)const
{
	Matrix4x4 m;

	for (int i{ 0 }; i < 4; i++)
	{
		m.col[i] = SIMDVectorMath::Add(col[i], _other.col[i]);
	}

	return m;
}

// 減算
Matrix4x4 Matrix4x4::operator-(const Matrix4x4& _other)const
{
	Matrix4x4 m;

	for (int i{ 0 }; i < 4; i++)
	{
		m.col[i] = SIMDVectorMath::Sub(col[i], _other.col[i]);
	}

	return m;
}

// 乗算
Matrix4x4 Matrix4x4::operator*(const Matrix4x4& _other)const
{

}

/// <summary>
/// 徐算(整数の場合static_castで整数になります)
/// </summary>
/// <returns>0徐算の場合は、そのままの値を返します</returns>
Matrix4x4 Matrix4x4::operator/(const Matrix4x4& _other)const
{

}

// 加算
Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& _other)
{
	for (int i{ 0 }; i < 4; i++)
	{
		col[i] = SIMDVectorMath::Add(col[i], _other.col[i]);
	}

	return *this;
}

// 減算
Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& _other)
{
	for (int i{ 0 }; i < 4; i++)
	{
		col[i] = SIMDVectorMath::Sub(col[i], _other.col[i]);
	}

	return *this;
}

// 乗算
Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& _other)
{

}

/// <summary>
/// 徐算(整数の場合static_castで整数になります)
/// </summary>
/// <returns>0徐算の場合は、そのままの値を返します</returns>
Matrix4x4& Matrix4x4::operator/=(const Matrix4x4& _other)
{

}

// スカラー倍
Matrix4x4 Matrix4x4::operator*(const float& _value) const
{
	Matrix4x4 m;

	for (int i{ 0 }; i < 4; i++)
	{
		m.col[i] = SIMDVectorMath::MulScalar(col[i], _value);
	}

	return m;
}

// スカラー割
Matrix4x4 Matrix4x4::operator/(const float& _value) const
{
	Matrix4x4 m;

	for (int i{ 0 }; i < 4; i++)
	{
		m.col[i] = SIMDVectorMath::DivScalar(col[i], _value);
	}

	return m;
}

// スカラー倍
Matrix4x4& Matrix4x4::operator*=(const float& _value)
{
	for (int i{ 0 }; i < 4; i++)
	{
		col[i] = SIMDVectorMath::MulScalar(col[i], _value);
	}

	return *this;
}

// スカラー割
Matrix4x4& Matrix4x4::operator/=(const float& _value) 
{
	for (int i{ 0 }; i < 4; i++)
	{
		col[i] = SIMDVectorMath::DivScalar(col[i], _value);
	}

	return *this;
}

// 一次変換
Vector3 Matrix4x4::operator *(const Vector3& _other) const 
{

}

// 一次変換
Vector3 Matrix4x4::operator *=(const Vector3& _other)const
{

}