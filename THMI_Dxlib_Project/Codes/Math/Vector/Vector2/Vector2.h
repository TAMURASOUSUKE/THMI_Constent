#pragma once

#include <type_traits>
#include "../SIMD/SIMDVector.h"

template<typename T>
struct alignas(16) Vector2
{
public:
public:
	static constexpr Vector2<T> ZERO{ 0.0,0.0 };
	static constexpr Vector2<T> ONE{ 1.0,1.0 };
	static constexpr Vector2<T> UP{ 0.0,-1.0 };
	static constexpr Vector2<T> DOWN{ 0.0,1.0 };
	static constexpr Vector2<T> LEFT{ -1.0,0.0 };
	static constexpr Vector2<T> RIGHT{ 1.0,0.0 };
public:
	union
	{
		// アクセス用数値
		struct 
		{
			float x;
			float y;
		};

		// SIMD計算用
		SIMDVector simd;
	};

public:
	// コンストラクタ
	Vector2() = default;
	
	/// <param name="_x">X</param>
	/// <param name="_y">Y</param>
	Vector2(T _x, T _y) :
		simd(_x,_y,0,0)
	{}

	// 加算
	Vector2<T> operator+(const Vector2<T>& _other)const;
	// 減算
	Vector2<T> operator-(const Vector2<T>& _other)const;
	// 乗算
	Vector2<T> operator*(float _value)const;
	/// <summary>
	/// 徐算(整数の場合static_castで整数になります)
	/// </summary>
	/// <returns>0徐算の場合は、そのままの値を返します</returns>
	Vector2<T> operator/(float _value)const;

	// 加算
	Vector2<T>& operator+=(const Vector2<T>& _other);
	// 減算
	Vector2<T>& operator-=(const Vector2<T>& _other);
	// 乗算
	Vector2<T>& operator*=(float _value);
	/// <summary>
	/// 徐算(整数の場合static_castで整数になります)
	/// </summary>
	/// <returns>0徐算の場合は、そのままの値を返します</returns>
	Vector2<T>& operator/=(float _value);

	// 逆ベクトル
	Vector2<T> operator-()const;

	// 等価
	bool operator==(const Vector2<T>& _other) const;
	// 不等価
	bool operator!=(const Vector2<T>& _other) const;

	// ベクトルの長さ(実数のみ)
	float Length() const requires std::is_floating_point_v<T>;
	// ベクトルの長さの2乗(実数のみ)
	float LengthSqr() const requires std::is_floating_point_v<T>;
	// 2つのベクトル間の距離(実数のみ)
	static float Distance(const Vector2<T>& _from, const Vector2<T>& _to) requires std::is_floating_point_v<T>;
	// 2つのベクトル間の距離の2乗(実数のみ)
	static float DistanceSqr(const Vector2<T>& _from, const Vector2<T>& _to) requires std::is_floating_point_v<T>;
	// 2つのベクトル間の角度(実数のみ)
	static float Angle(const Vector2<T>& _from, const Vector2<T>& _to) requires std::is_floating_point_v<T>;

	// 正規化(値の変化有)(実数のみ)
	Vector2<T>& Normalize() requires std::is_floating_point_v<T>;
	// 正規化(値の変化有)(実数のみ)
	static Vector2<T>& Normalize(const Vector2<T>& _vec) requires std::is_floating_point_v<T>;

	// 正規化(値の変化無)(実数のみ)
	Vector2<T> Normalized() requires std::is_floating_point_v<T>;
	// 正規化(値の変化無)(実数のみ)
	static Vector2<T> Normalized(const Vector2<T>& _vec) requires std::is_floating_point_v<T>;

	// 内積
	static float Dot(const Vector2<T>& _vec1, const Vector2<T>& _vec2);
	// 外積
	static float Cross(const Vector2<T>& _vec1, const Vector2<T>& _vec2);
};