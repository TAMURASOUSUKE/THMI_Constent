#include "../SIMD/SIMDVectorMath.h"
#include "Vector2.h"

// 加算
template<typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& _other) const
{
	return SIMDVectorMath::Add(simd, _other.simd);
}

// 減算
template<typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& _other)const
{
	return SIMDVectorMath::Sub(simd, _other.simd);
}

// 乗算
template<typename T>
Vector2<T> Vector2<T>::operator*(float _value)const
{
	return SIMDVectorMath::MulScalar(simd, _value);
}

/// <summary>
/// 徐算(整数の場合static_castで整数になります)
/// </summary>
/// <returns>0徐算の場合は、そのままの値を返します</returns>
template<typename T>
Vector2<T> Vector2<T>::operator/(float _value)const
{
	return SIMDVectorMath::DivScalar(simd, _value);
}

// 加算
template<typename T>
Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& _other)
{
	return simd = SIMDVectorMath::Add(simd, _other.simd);
}

// 減算
template<typename T>
Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& _other)
{
	return simd = SIMDVectorMath::Sub(simd, _other.simd);
}

// 乗算
template<typename T>
Vector2<T>& Vector2<T>::operator*=(float _value)
{
	return simd = SIMDVectorMath::MulScalar(simd, _value);
}

/// <summary>
/// 徐算(整数の場合static_castで整数になります)
/// </summary>
/// <returns>0徐算の場合は、そのままの値を返します</returns>
template<typename T>
Vector2<T>& Vector2<T>::operator/=(float _value)
{
	return simd = SIMDVectorMath::DivScalar(simd, _value);
}

// 逆ベクトル
template<typename T>
Vector2<T> Vector2<T>::operator-()const
{
	return SIMDVectorMath::Negate(simd);
}

// 等価
template<typename T>
bool Vector2<T>::operator==(const Vector2<T>& _other) const
{

}

// 不等価
template<typename T>
bool Vector2<T>::operator!=(const Vector2<T>& _other) const
{

}

// ベクトルの長さ(実数のみ)
template<typename T>
float Vector2<T>::Length() const requires std::is_floating_point_v<T>
{
	return SIMDVectorMath::Length2(simd);
}

// ベクトルの長さの2乗(実数のみ)
template<typename T>
float Vector2<T>::LengthSqr() const requires std::is_floating_point_v<T>
{
	return SIMDVectorMath::Dot2(simd, simd);
}

// 2つのベクトル間の距離(実数のみ)
template<typename T>
static float Vector2<T>::Distance(const Vector2<T>& _from, const Vector2<T>& _to) requires std::is_floating_point_v<T>
{
	return SIMDVectorMath::Length2((_to - _from).simd);
}

// 2つのベクトル間の距離の2乗(実数のみ)
template<typename T>
static float Vector2<T>::DistanceSqr(const Vector2<T>& _from, const Vector2<T>& _to) requires std::is_floating_point_v<T>
{
	Vector2<T> dist{ _to - _from };
	return SIMDVectorMath::Dot2(dist, dist);
}

// 2つのベクトル間の角度(実数のみ)
template<typename T>
static float Vector2<T>::Angle(const Vector2<T>& _from, const Vector2<T>& _to) requires std::is_floating_point_v<T>
{
	float fromLen = _from.Length();
	float toLen = _to.Length();

	if (fromLen == 0 || toLen == 0)
	{
		return 0.0f;
	}

	return acosf(Dot(_from, _to) / (fromLen * toLen));
}

// 正規化(値の変化有)(実数のみ)
template<typename T>
Vector2<T>& Vector2<T>::Normalize() requires std::is_floating_point_v<T>
{
	return simd = SIMDVectorMath::Normalize(simd);
}

// 正規化(値の変化有)(実数のみ)
template<typename T>
static Vector2<T>& Vector2<T>::Normalize(const Vector2<T>& _vec) requires std::is_floating_point_v<T>
{
	return simd = SIMDVectorMath::Normalize(_vec.simd);
}

// 正規化(値の変化無)(実数のみ)
template<typename T>
Vector2<T> Vector2<T>::Normalized() requires std::is_floating_point_v<T>
{
	return SIMDVectorMath::Normalize(simd);
}

// 正規化(値の変化無)(実数のみ)
template<typename T>
static Vector2<T> Vector2<T>::Normalized(const Vector2<T>& _vec) requires std::is_floating_point_v<T>
{
	return SIMDVectorMath::Normalize(_vec.simd);
}

// 内積
template<typename T>
static float Vector2<T>::Dot(const Vector2<T>& _vec1, const Vector2<T>& _vec2)
{
	return SIMDVectorMath::Dot2(_vec1, _vec2);
}

// 外積
template<typename T>
static float Vector2<T>::Cross(const Vector2<T>& _vec1, const Vector2<T>& _vec2)
{
	return _vec1.x * _vec2.y - _vec2.x * _vec1.y;
}