#include <smmintrin.h>
#include <math.h>
#include "SIMDVectorMath.h"

// 加算
SIMDVector SIMDVectorMath::Add(const SIMDVector& _vec1, const SIMDVector& _vec2)
{
	return _mm_add_ps(_vec1, _vec2);
}

// 減算
SIMDVector SIMDVectorMath::Sub(const SIMDVector& _vec1, const SIMDVector& _vec2)
{
	return _mm_sub_ps(_vec1, _vec2);
}

// 乗算
SIMDVector SIMDVectorMath::Mul(const SIMDVector& _vec1, const SIMDVector& _vec2)
{
	return _mm_mul_ps(_vec1, _vec2);
}

// 割り算
SIMDVector SIMDVectorMath::Div(const SIMDVector& _vec1, const SIMDVector& _vec2)
{
	return _mm_div_ps(_vec1, _vec2);
}

// スカラー倍
SIMDVector SIMDVectorMath::MulScalar(const SIMDVector& _vec, float _value)
{
	return Mul(_vec, SIMDVector(_value));
}

// スカラー割
SIMDVector SIMDVectorMath::DivScalar(const SIMDVector& _vec, float _value)
{
	return Div(_vec, SIMDVector(_value));
}

// 内積(Vector2)
float SIMDVectorMath::Dot2(const SIMDVector& _vec1, const SIMDVector& _vec2)
{
	return _mm_cvtss_f32(_mm_dp_ps(_vec1, _vec2, 0x31));
}

// 内積(Vector3)
float SIMDVectorMath::Dot3(const SIMDVector& _vec1, const SIMDVector& _vec2)
{
	return _mm_cvtss_f32(_mm_dp_ps(_vec1, _vec2, 0x71));
}

// 外積(Vector3)
SIMDVector SIMDVectorMath::Cross3(const SIMDVector& _vec1, const SIMDVector& _vec2)
{
	SIMDVector yzx{ SIMDVector::Shuffle<1,2,0,3>(_vec1) };
	SIMDVector zxy{ SIMDVector::Shuffle<2,0,1,3>(_vec2) };

	// 左側の掛け算
	SIMDVector temp1{ Mul(yzx ,zxy) };

	zxy = SIMDVector::Shuffle<2, 0, 1, 3>(_vec1);
	yzx = SIMDVector::Shuffle<1, 2, 0, 3>(_vec2);

	// 右の掛け算
	SIMDVector temp2{ Mul(zxy,yzx) };

	// 引き算
	return Sub(temp1, temp2);
}

// 長さ(Vector2)
float SIMDVectorMath::Length2(const SIMDVector& _vec)
{
	return sqrt(Dot2(_vec, _vec));
}

// 長さ(Vector3)
float SIMDVectorMath::Length3(const SIMDVector& _vec)
{
	return sqrt(Dot3(_vec, _vec));
}

// 正規化
SIMDVector SIMDVectorMath::Normalize(const SIMDVector& _vec)
{
	SIMDVector rsqrt{ RSqrt(_vec) };
	
	return Mul(_vec, rsqrt);
}

// 平方根
SIMDVector SIMDVectorMath::Sqrt(const SIMDVector& _vec)
{
	return _mm_sqrt_ps(_vec);
}

// 逆平方根
SIMDVector SIMDVectorMath::RSqrt(const SIMDVector& _vec)
{
	SIMDVector rsqrt{ _mm_rsqrt_ps(_vec) };

	SIMDVector half{ 0.5f };
	SIMDVector three{ 3.0f };

	// ニュートン法で補正
	return Mul(rsqrt, Mul(Sub(three, Mul(_vec, Mul(rsqrt, rsqrt))), half));
}

// 逆数
SIMDVector SIMDVectorMath::Reciprocal(const SIMDVector& _vec)
{
	return _mm_rcp_ps(_vec);
}

// 反転
SIMDVector SIMDVectorMath::Negate(const SIMDVector& _vec)
{
	return(Sub(_mm_setzero_ps(), _vec));
}