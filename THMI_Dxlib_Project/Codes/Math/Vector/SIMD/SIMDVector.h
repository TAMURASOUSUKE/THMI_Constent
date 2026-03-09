#pragma once

#include <xmmintrin.h>

// 128bit SIMDレジスタラッパー構造体なので、ヘッダ内で収める

struct alignas(16) SIMDVector
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
		value{ _mm_set_ps(_w,_z,_y,_x) }
	{}

	// splat
	SIMDVector(float v):
		value{ _mm_set1_ps(v) }
	{}

	// 型変換演算子
	operator __m128() const
	{
		return value;
	}

	/// <summary>
	/// 値引き出し関数
	/// </summary>
	/// <param name="_ptr">最初の値のアドレス</param>
	void Store(float* _ptr)const
	{
		_mm_store_ps(_ptr, value);
	}

	/// <summary>
	/// 値入れ替え
	/// </summary>
	/// <typeparam name="X">値1がどこと変わるか</typeparam>
	/// <typeparam name="Y">値1がどこと変わるか</typeparam>
	/// <typeparam name="Z">値1がどこと変わるか</typeparam>
	/// <typeparam name="W">値1がどこと変わるか</typeparam>
	/// <param name="_value">入れ替える元の値</param>
	/// <returns>入れ替えられた新しい値</returns>
	template<int X,int Y,int Z,int W>
	static SIMDVector Shuffle(const SIMDVector& _value)
	{
		return _mm_shuffle_ps(_value, _value, _MM_SHUFFLE(W, Z, Y, X));
	}
};