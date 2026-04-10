#include "../SIMD/SIMDVectorMath.h"
#include "Vector3Int.h"

// 加算
Vector3Int Vector3Int::operator+(const Vector3Int& _other) const
{
	return SIMDVectorMath::Add(simd, _other.simd);
}

// 減算
Vector3Int Vector3Int::operator-(const Vector3Int& _other)const
{
	return SIMDVectorMath::Sub(simd, _other.simd);
}

// 乗算
Vector3Int Vector3Int::operator*(float _value)const
{
	return SIMDVectorMath::MulScalar(simd, _value);
}

// 加算
Vector3Int& Vector3Int::operator+=(const Vector3Int& _other)
{
	simd = SIMDVectorMath::Add(simd, _other.simd);
	return *this;
}

// 減算
Vector3Int& Vector3Int::operator-=(const Vector3Int& _other)
{
	simd = SIMDVectorMath::Sub(simd, _other.simd);
	return *this;
}

// 乗算
Vector3Int& Vector3Int::operator*=(float _value)
{
	simd = SIMDVectorMath::MulScalar(simd, _value);
	return *this;
}

// 等価
bool Vector3Int::operator==(const Vector3Int& _other) const
{
	return SIMDVectorMath::Equals(simd, _other.simd);
}

// 不等価
bool Vector3Int::operator!=(const Vector3Int& _other) const
{
	return !SIMDVectorMath::Equals(simd, _other.simd);
}