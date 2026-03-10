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
	// アクセス用数値
	union
	{
		struct 
		{
			float x;
			float y;
		};

		SIMDVector value;
	};

public:
	// コンストラクタ
	Vector2() = default;
	
	/// <param name="_x">X</param>
	/// <param name="_y">Y</param>
	Vector2(T _x, T _y) :
		value(_x,_y,0,0)
	{}

	// 加算
	Vector2<T> operator+(const Vector2<T>& other)const;
	// 減算
	Vector2<T> operator-(const Vector2<T>& other)const;
	// 乗算
	Vector2<T> operator*(float value)const;
	/// <summary>
	/// 徐算(整数の場合static_castで整数になります)
	/// </summary>
	/// <returns>0徐算の場合は、そのままの値を返します</returns>
	Vector2<float> operator/(float value)const;

	// 加算
	Vector2<T>& operator+=(const Vector2<T>& other);
	// 減算
	Vector2<T>& operator-=(const Vector2<T>& other);
	// 乗算
	Vector2<T>& operator*=(float value);
	/// <summary>
	/// 徐算(整数の場合static_castで整数になります)
	/// </summary>
	/// <returns>0徐算の場合は、そのままの値を返します</returns>
	Vector2<T>& operator/=(float value);

	// 逆ベクトル
	Vector2<T> operator-()const;

	// 等価
	bool operator==(const Vector2& other) const;
	// 不等価
	bool operator!=(const Vector2& other) const;

	// ベクトルの長さ(実数のみ)
	float Length() const requires std::is_floating_point<T>;
	// ベクトルの長さの2乗(実数のみ)
	float LengthSqr() const requires std::is_floating_point<T>;
	// 2つのベクトル間の距離(実数のみ)
	static float Distance(const Vector2& from, const Vector2& to) requires std::is_floating_point<T>;
	// 2つのベクトル間の距離の2乗(実数のみ)
	static float DistanceSqr(const Vector2& from, const Vector2& to) requires std::is_floating_point<T>;
	// 2つのベクトル間の角度(実数のみ)
	static float Angle(const Vector2& from, const Vector2& to) requires std::is_floating_point<T>;

	// 正規化(値の変化なし)(実数のみ)
	Vector2<float> Normalize() requires std::is_floating_point<T>;
	// 正規化(値の変化なし)(実数のみ)
	static Vector2<float> Normalize(const Vector2& vec) requires std::is_floating_point<T>;

	// 正規化(値の変化あり)(実数のみ)
	Vector2<float> Normalized() requires std::is_floating_point<T>;
	// 正規化(値の変化あり)(実数のみ)
	static Vector2<float> Normalized(const Vector2& vec) requires std::is_floating_point<T>;

	// 内積
	static float Dot(const Vector2& vec1, const Vector2& vec2);
	// 外積
	static float Cross(const Vector2& vec1, const Vector2& vec2);
};