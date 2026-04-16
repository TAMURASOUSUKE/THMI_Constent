#include "../Vector/SIMD/SIMDVectorMath.h"
#include "MatGenerateFunc.h"

Matrix4x4 MatGenerateFunc::Translate(const Vector3& _vec)
{
	return Matrix4x4{
		1.0f,0.0f,0.0f,_vec.x,
		0.0f,1.0f,0.0f,_vec.y,
		0.0f,0.0f,1.0f,_vec.z,
		0.0f,0.0f,0.0f,1.0f,
	};
}

Matrix4x4 MatGenerateFunc::Scale(const Vector3& _scale)
{
	return Matrix4x4
	{
		_scale.x,0.0f,0.0f,0.0f,
		0.0f,_scale.y,0.0f,0.0f,
		0.0f,0.0f,_scale.x,0.0f,
		0.0f,0.0f,0.0f,1.0f,
	};
}

Matrix4x4 MatGenerateFunc::Rotate(const Quaternion& _rot)
{
	// 二乗
	SIMDVectorFloat sqr{ SIMDVectorMath::Mul(_rot.simd,_rot.simd) };

	// yzxw
	SIMDVectorFloat yzxw{ SIMDVectorFloat::Shuffle<1,2,0,3>(_rot.simd) };
	// zxyw
	SIMDVectorFloat zxyw{ SIMDVectorFloat::Shuffle<2,0,1,3>(_rot.simd) };

	// xy yz zx
	SIMDVectorFloat mul1{ SIMDVectorMath::Mul(_rot.simd,yzxw) };
	// xz yx zy
	SIMDVectorFloat mul2{ SIMDVectorMath::Mul(_rot.simd,zxyw) };

	// 二倍
	mul1 = SIMDVectorMath::MulScalar(mul1, 2.0f);
	mul2 = SIMDVectorMath::MulScalar(mul2, 2.0f);
	sqr = SIMDVectorMath::MulScalar(sqr, 2.0f);

	// 
}

Matrix4x4 MatGenerateFunc::RotateX(float _rad)
{

}

Matrix4x4 MatGenerateFunc::RotateY(float _rad)
{

}

Matrix4x4 MatGenerateFunc::RotateZ(float _rad)
{

}

Matrix4x4 MatGenerateFunc::TRS(const Vector3& _vec, const Quaternion& _rot, const Vector3& _scale)
{
	return Translate(_vec) * Rotate(_rot) * Scale(_scale);
}

Matrix4x4 MatGenerateFunc::LookAt(const Vector3& _eye, const Vector3& _target, const Vector3& _up)
{

}