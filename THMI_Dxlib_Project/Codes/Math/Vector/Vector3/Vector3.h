#pragma once

#include "../SIMD/SIMDVector.h"

struct alignas(16) Vector3
{
public:
	union
	{
		// アクセス用数値
		struct
		{
			float x;
			float y;
			float z;
			float pad;
		};

		// SIMD計算用
		SIMDVectorFloat simd;
	};

public:
	// コンストラクタ
	Vector3() = default;

	/// <param name="simd">SIMD</param>
	Vector3(SIMDVectorFloat simd) :
		simd(simd)
	{
	}

	/// <param name="_x">X</param>
	/// <param name="_y">Y</param>
	Vector3(float _x, float _y) :
		simd(_x, _y, 0, 0)
	{
	}

	// 型変換
	operator SIMDVectorFloat() const
	{
		return simd;
	}

	// 加算
	Vector3 operator+(const Vector3& _other)const;
	// 減算
	Vector3 operator-(const Vector3& _other)const;
	// 乗算
	Vector3 operator*(float _value)const;
	/// <summary>
	/// 徐算(整数の場合static_castで整数になります)
	/// </summary>
	/// <returns>0徐算の場合は、そのままの値を返します</returns>
	Vector3 operator/(float _value)const;

	// 加算
	Vector3& operator+=(const Vector3& _other);
	// 減算
	Vector3& operator-=(const Vector3& _other);
	// 乗算
	Vector3& operator*=(float _value);
	/// <summary>
	/// 徐算(整数の場合static_castで整数になります)
	/// </summary>
	/// <returns>0徐算の場合は、そのままの値を返します</returns>
	Vector3& operator/=(float _value);

	// 逆ベクトル
	Vector3 operator-()const;

	// 等価
	bool operator==(const Vector3& _other) const;
	// 不等価
	bool operator!=(const Vector3& _other) const;

	// ベクトルの長さ(実数のみ)
	float Length() const;
	// ベクトルの長さの2乗(実数のみ)
	float LengthSqr() const;
	// 2つのベクトル間の距離(実数のみ)
	static float Distance(const Vector3& _from, const Vector3& _to);
	// 2つのベクトル間の距離の2乗(実数のみ)
	static float DistanceSqr(const Vector3& _from, const Vector3& _to);
	// 2つのベクトル間の角度(実数のみ)
	static float Angle(const Vector3& _from, const Vector3& _to);

	// 正規化(値の変化有)(実数のみ)
	Vector3& Normalize();
	// 正規化(値の変化有)(実数のみ)
	static Vector3& Normalize(Vector3& _vec);

	// 正規化(値の変化無)(実数のみ)
	Vector3 Normalized();
	// 正規化(値の変化無)(実数のみ)
	static Vector3 Normalized(const Vector3& _vec);

	// 内積
	static float Dot(const Vector3& _vec1, const Vector3& _vec2);
	// 外積
	static Vector3 Cross(const Vector3& _vec1, const Vector3& _vec2);
};