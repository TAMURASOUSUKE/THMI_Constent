#pragma once

#include "../SIMD/SIMDVector.h"

struct alignas(16) Vector2Int
{
public:
	union
	{
		// アクセス用数値
		struct
		{
			int x;
			int y;
			int pad[2];
		};

		// SIMD計算用
		SIMDVectorInt simd;
	};
public:
	// コンストラクタ
	Vector2Int() = default;

	/// <param name="simd">SIMD</param>
	Vector2Int(SIMDVectorInt simd) :
		simd(simd)
	{
	}

	/// <param name="_x">X</param>
	/// <param name="_y">Y</param>
	Vector2Int(int _x, int _y) :
		simd(_x, _y, 0, 0)
	{
	}

	// 型変換
	operator SIMDVectorInt() const
	{
		return simd;
	}

	// 加算
	Vector2Int operator+(const Vector2Int& _other)const;
	// 減算
	Vector2Int operator-(const Vector2Int& _other)const;
	// 乗算
	Vector2Int operator*(float _value)const;

	// 加算
	Vector2Int& operator+=(const Vector2Int& _other);
	// 減算
	Vector2Int& operator-=(const Vector2Int& _other);
	// 乗算
	Vector2Int& operator*=(float _value);

	// 等価
	bool operator==(const Vector2Int& _other) const;
	// 不等価
	bool operator!=(const Vector2Int& _other) const;
};