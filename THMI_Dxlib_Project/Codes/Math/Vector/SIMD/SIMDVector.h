#pragma once

#include <xmmintrin.h>

// 128bit SIMDレジスタラッパー構造体なので、ヘッダ内で収める

struct SIMDVector
{
public:
	__m128 value;
public:
	// コンストラクタ
	SIMDVector():
		value{ _mm_setzero_ps()}
	{}

	/// <param name="_value"></param>
	SIMDVector(__m128 _value):
		value{ _value }
	{}

	/// <param name="_ptr">最初の値のアドレス</param>
	SIMDVector(const float* _ptr) :
		value{ _mm_load_ps(_ptr) }
	{}

	/// <param name="_x">値1</param>
	/// <param name="_y">値2</param>
	/// <param name="_z">値3</param>
	/// <param name="_w">値4</param>
	SIMDVector(float _x, float _y, float _z, float _w) :
		value{ _mm_setr_ps(_x,_y,_z,_w) }
	{}

	/// <summary>
	/// 値引き出し関数
	/// </summary>
	/// <param name="_ptr">最初の値のアドレス</param>
	void Store(float* _ptr)const
	{
		_mm_store_ps(_ptr, value);
	}

	// 加算
	SIMDVector operator+(const SIMDVector& _other) const
	{
		return SIMDVector(_mm_add_ps(value, _other.value));
	}

	// 減算
	SIMDVector operator-(const SIMDVector& _other) const
	{
		return SIMDVector(_mm_sub_ps(value, _other.value));
	}

	// 乗算
	SIMDVector operator*(const SIMDVector& _other) const
	{
		return SIMDVector(_mm_mul_ps(value, _other.value));
	}
};