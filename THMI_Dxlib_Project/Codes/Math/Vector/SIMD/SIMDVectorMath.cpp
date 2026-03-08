#include "SIMDVectorMath.h"

// 加算
SIMDVector SIMDVectorMath::Add(const SIMDVector& _vec1, const SIMDVector& _vec2)
{
	return _vec1 + _vec2;
}

// 減算
SIMDVector SIMDVectorMath::Sub(const SIMDVector& _vec1, const SIMDVector& _vec2)
{
	return _vec1 - _vec2;
}

// 乗算
SIMDVector SIMDVectorMath::Mul(const SIMDVector& _vec1, const SIMDVector& _vec2)
{
	return _vec1 * _vec2;
}

// 割り算
SIMDVector SIMDVectorMath::Div(const SIMDVector& _vec1, const SIMDVector& _vec2)
{
	return _mm_div_ps(_vec1.value, _vec2.value);
}

// スカラー倍
SIMDVector SIMDVectorMath::MulScalar(const SIMDVector& _vec, float _value)
{

}

// スカラー割
SIMDVector SIMDVectorMath::DivScalar(const SIMDVector& _vec, float _value)
{

}

// 内積(Vector2)
float SIMDVectorMath::Dot2(const SIMDVector& _vec1, const SIMDVector& _vec2)
{

}

// 内積(Vector3)
float SIMDVectorMath::Dot3(const SIMDVector& _vec1, const SIMDVector& _vec2)
{

}

// 外積(Vector3)
SIMDVector SIMDVectorMath::Cross3(const SIMDVector& _vec1, const SIMDVector& _vec2)
{

}

// 長さ(Vector2)
float SIMDVectorMath::Length2(const SIMDVector& _vec)
{

}

// 長さ(Vector3)
float SIMDVectorMath::Length3(const SIMDVector& _vec)
{

}

// 正規化(Vector2)
SIMDVector SIMDVectorMath::Normalize2(const SIMDVector& _vec)
{

}

// 正規化(Vector3)
SIMDVector SIMDVectorMath::Normalize3(const SIMDVector& _vec)
{

}

// 平方根
SIMDVector SIMDVectorMath::Sqrt(const SIMDVector& _vec)
{

}

// 逆平方根
SIMDVector SIMDVectorMath::RSqrt(const SIMDVector& _vec)
{

}

// 逆数
SIMDVector SIMDVectorMath::Reciprocal(const SIMDVector& _vec)
{

}

// 反転
SIMDVector SIMDVectorMath::Negate(const SIMDVector& _vec)
{

}

// BroadCast
SIMDVector SIMDVectorMath::Splat(float _value)
{

}