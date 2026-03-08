#pragma once

#include "SIMDVector.h"

namespace SIMDVectorMath
{
	// 加算
	SIMDVector Add(const SIMDVector& _vec1, const SIMDVector& _vec2);
	// 減算
	SIMDVector Sub(const SIMDVector& _vec1, const SIMDVector& _vec2);
	// 乗算
	SIMDVector Mul(const SIMDVector& _vec1, const SIMDVector& _vec2);
	// 割り算
	SIMDVector Div(const SIMDVector& _vec1, const SIMDVector& _vec2);

	// スカラー倍
	SIMDVector MulScalar(const SIMDVector& _vec, float _value);
	// スカラー割
	SIMDVector DivScalar(const SIMDVector& _vec, float _value);

	// 内積(Vector2)
	float Dot2(const SIMDVector& _vec1, const SIMDVector& _vec2);
	// 内積(Vector3)
	float Dot3(const SIMDVector& _vec1, const SIMDVector& _vec2);
	// 外積(Vector3)
	SIMDVector Cross3(const SIMDVector& _vec1, const SIMDVector& _vec2);

	// 長さ(Vector2)
	float Length2(const SIMDVector& _vec);
	// 長さ(Vector3)
	float Length3(const SIMDVector& _vec);
	// 正規化(Vector2)
	SIMDVector Normalize2(const SIMDVector& _vec);
	// 正規化(Vector3)
	SIMDVector Normalize3(const SIMDVector& _vec);

	// 平方根
	SIMDVector Sqrt(const SIMDVector& _vec);
	// 逆平方根
	SIMDVector RSqrt(const SIMDVector& _vec);

	// 逆数
	SIMDVector Reciprocal(const SIMDVector& _vec);

	// 反転
	SIMDVector Negate(const SIMDVector& _vec);

	// BroadCast
	SIMDVector Splat(float _value);
};