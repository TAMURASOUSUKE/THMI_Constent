#pragma once

#include "../SIMD/SIMDVector.h"

struct alignas(16) Vector3Int
{
public:
	union
	{
		// アクセス用数値
		struct
		{
			int x;
			int y;
			int z;
			int pad;
		};

		// SIMD計算用
		SIMDVectorInt simd;
	};
public:
	// コンストラクタ
	Vector3Int() = default;

	/// <param name="simd">SIMD</param>
	Vector3Int(SIMDVectorInt simd) :
		simd(simd)
	{
	}

	/// <param name="_x">X</param>
	/// <param name="_y">Y</param>
	Vector3Int(int _x, int _y) :
		simd(_x, _y, 0, 0)
	{
	}

	// 型変換
	operator SIMDVectorInt() const
	{
		return simd;
	}

	// 加算
	Vector3Int operator+(const Vector3Int& _other)const;
	// 減算
	Vector3Int operator-(const Vector3Int& _other)const;
	// 乗算
	Vector3Int operator*(float _value)const;

	// 加算
	Vector3Int& operator+=(const Vector3Int& _other);
	// 減算
	Vector3Int& operator-=(const Vector3Int& _other);
	// 乗算
	Vector3Int& operator*=(float _value);

	// 等価
	bool operator==(const Vector3Int& _other) const;
	// 不等価
	bool operator!=(const Vector3Int& _other) const;
};