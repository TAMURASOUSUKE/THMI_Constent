#include "../Vector/SIMD/SIMDVectorMath.h"
#include "MatGenerateFunc.h"

#include "DirectXMath.h"

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
	// 2_rot
	SIMDVectorFloat rot2{ SIMDVectorMath::Add(_rot.simd, _rot.simd) };
	// 2_rot^2
	SIMDVectorFloat rotrot2{ SIMDVectorMath::Mul(_rot.simd, rot2) };

	// y^2 x^2 x^2 w^2
	SIMDVectorFloat v0{ SIMDVectorFloat::Shuffle<1,0,0,3>(rotrot2) };
	// z^2 z^2 y^2 w^2
	SIMDVectorFloat v1{ SIMDVectorFloat::Shuffle<2,2,1,3>(rotrot2) };

	SIMDVectorFloat one{ 1.0f };

	// 1 - v0 - v1
	SIMDVectorFloat elementDiagonal{ SIMDVectorMath::Sub(one,v0) };
	// 対角要素
	elementDiagonal = SIMDVectorMath::Sub(elementDiagonal, v1); // 1 - 2y^2 - 2z^2, 1 - 2x^2 - 2z^2, 1 - x^2 - y^2

	// wがない項を作る
	// x,x,y,w
	v0 = SIMDVectorFloat::Shuffle<0, 0, 1, 3>(_rot.simd);
	// 2y,2z,2z,2w
	v1 = SIMDVectorFloat::Shuffle<1, 2, 2, 3>(rot2);
	// 2xy,2xz,2yz,2w^2
	SIMDVectorFloat termXyz{ SIMDVectorMath::Mul(v0,v1) };

	// wの項を作る
	// 2xw,2yw,2zw,2w^2
	SIMDVectorFloat termW{ SIMDVectorMath::MulScalar(rot2,_rot.w) };
	// 2zw,2yw,2xw,2w^2
	termW = SIMDVectorFloat::Shuffle<2, 1, 0, 3>(termW);

	// 加算の要素
	// 2xy + 2zw, 2xz + 2yw, 2yz + 2xw
	SIMDVectorFloat elementAdd{ SIMDVectorMath::Add(termXyz,termW) };
	// 2xy + 2zw, 2yz + 2xw, 2xz + 2yw
	elementAdd = SIMDVectorFloat::Shuffle<0, 2, 1, 3>(elementAdd);
	// 減算の要素
	// 2xy - 2zw, 2xz - 2yw, 2yz - 2xw
	SIMDVectorFloat elementSub{ SIMDVectorMath::Sub(termXyz,termW) };
	// 2yz - 2yw, 2xy - 2zw, 2yz - 2xw
	elementSub = SIMDVectorFloat::Shuffle<1, 0, 2, 3>(elementSub);

	// 行ごとに要素を構築
	Matrix4x4 m;
	return m;
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