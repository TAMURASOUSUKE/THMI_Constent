#pragma once

#include "../Vector/Vector3/Vector3.h"

class Matrix4x4
{
public:
	union
	{
		// アクセス用
		float m[4][4];
		// SIMD演算用
		struct { SIMDVectorFloat col[4]; };
	};

public:
	// コンストラクタ(すべて0)
	Matrix4x4()
	{
		col[0] = SIMDVectorFloat{};
		col[1] = SIMDVectorFloat{};
		col[2] = SIMDVectorFloat{};
		col[3] = SIMDVectorFloat{};
	}

	// すべての要素を引数の値にする
	Matrix4x4(float _value) :
		col(_value)
	{
	}

	// 入れた値がそのまま行列になる
	Matrix4x4(
		float _m00, float _m01, float _m02, float _m03,
		float _m10, float _m11, float _m12, float _m13,
		float _m20, float _m21, float _m22, float _m23,
		float _m30, float _m31, float _m32, float _m33
	)
	{
		col[0] = SIMDVectorFloat{ _m00,_m01,_m02,_m03 };
		col[1] = SIMDVectorFloat{ _m10,_m11,_m12,_m13 };
		col[2] = SIMDVectorFloat{ _m20,_m21,_m22,_m23 };
		col[3] = SIMDVectorFloat{ _m30,_m31,_m32,_m33 };
	}

	Matrix4x4 Identity();

	// 加算
	Matrix4x4 operator+(const Matrix4x4& _other)const;
	// 減算
	Matrix4x4 operator-(const Matrix4x4& _other)const;
	// 乗算
	Matrix4x4 operator*(const Matrix4x4& _other)const;
	/// <summary>
	/// 徐算(整数の場合static_castで整数になります)
	/// </summary>
	/// <returns>0徐算の場合は、そのままの値を返します</returns>
	Matrix4x4 operator/(const Matrix4x4& _other)const;

	// 加算
	Matrix4x4& operator+=(const Matrix4x4& _other);
	// 減算
	Matrix4x4& operator-=(const Matrix4x4& _other);
	// 乗算
	Matrix4x4& operator*=(const Matrix4x4& _other);
	/// <summary>
	/// 徐算(整数の場合static_castで整数になります)
	/// </summary>
	/// <returns>0徐算の場合は、そのままの値を返します</returns>
	Matrix4x4& operator/=(const Matrix4x4& _other);

	// スカラー倍
	Matrix4x4 operator*(const float& _value) const;
	// スカラー割
	Matrix4x4 operator/(const float& _value) const;

	// スカラー倍
	Matrix4x4& operator*=(const float& _value);
	// スカラー割
	Matrix4x4& operator/=(const float& _value);

	// 一次変換
	Vector3 operator *(const Vector3& _other) const;

	// 一次変換
	Vector3 operator *=(const Vector3& _other)const;
};