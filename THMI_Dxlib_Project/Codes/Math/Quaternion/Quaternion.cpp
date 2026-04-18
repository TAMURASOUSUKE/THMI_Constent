#include <math.h>
#include "../Vector/SIMD/SIMDVectorMath.h"
#include "../Matrix/MatGenerateFunc.h"
#include "Quaternion.h"

// 単位
Quaternion Quaternion::Identity()
{
	return Quaternion{ 0,0,0,1 };
}

// 正規化
Quaternion Quaternion::Normalized()
{
	return SIMDVectorMath::Normalize(simd);
}

// 正規化
Quaternion& Quaternion::Normalize()
{
	simd = SIMDVectorMath::Normalize(simd);
	return *this;
}

// 正規化
Quaternion Quaternion::Normalized(Quaternion& _rot)
{
	return SIMDVectorMath::Normalize(_rot.simd);
}

// 正規化
Quaternion& Quaternion::Normalize(Quaternion& _rot)
{
	_rot.simd = SIMDVectorMath::Normalize(_rot.simd);
	return _rot;
}

// 乗法
Quaternion Quaternion::operator*(const Quaternion& _value) const
{
	// 実部
	float ansW{ w * _value.w + SIMDVectorMath::Dot3(simd,_value.simd) };

	// 虚部
	// w1 * v2 + w2 * v1 + v1 × v2
	SIMDVectorFloat vec
	{
		SIMDVectorMath::Add(
			SIMDVectorMath::Add(
				SIMDVectorMath::MulScalar(_value.simd,w),SIMDVectorMath::MulScalar(simd,_value.w))
			,SIMDVectorMath::Cross3(simd,_value.simd))
	};

	// 実部と虚部の合成
	return Quaternion{ SIMDVectorFloat::Blend<0x0001>(vec,ansW) };
}

// 乗法
Quaternion Quaternion::operator*=(const Quaternion& _value)
{
	// 実部
	float ansW = w * _value.w + SIMDVectorMath::Dot3(simd, _value.simd);

	// 虚部
	// w1 * v2 + w2 * v1 + v1 × v2
	SIMDVectorFloat vec
	{
		SIMDVectorMath::Add(
			SIMDVectorMath::Add(
				SIMDVectorMath::MulScalar(_value.simd,w), // w1 * v2
				SIMDVectorMath::MulScalar(simd,_value.w)) // w2 * v1
			,SIMDVectorMath::Cross3(simd,_value.simd)) //  v1 × v2
	};

	simd = SIMDVectorFloat::Blend<0x0001>(vec, ansW);

	return *this;
}

// 逆数
Quaternion Quaternion::Inverse() const
{
	// 内積
	float dot{ SIMDVectorMath::Dot4(simd,simd) };
	// ノルム
	float norm{ sqrtf(dot) };
	// simd / norm
	return SIMDVectorMath::DivScalar(this->Conjugate().simd, norm);
}

// 共役
Quaternion Quaternion::Conjugate()const
{
	return { -x,-y,-z,w };
}

// 軸と角とで回転
Quaternion Quaternion::AngleAxis(float _rad, const Vector3& _axis)
{
	float angleHalf{ _rad / 2.0f };

	float sin{ sinf(angleHalf) };
	float cos{ cosf(angleHalf) };

	return
	{
		_axis.x * sin,
		_axis.y * sin,
		_axis.z * sin,
		cos
	};
}

// オイラー角から生成
Quaternion Quaternion::Euler(float _pitch, float _yaw, float _roll)
{
	// yaw
	float cy = cos(_yaw * 0.5f);
	float sy = sin(_yaw * 0.5f);
	// pitch
	float cp = cos(_pitch * 0.5f);
	float sp = sin(_pitch * 0.5f);
	// roll
	float cr = cos(_roll * 0.5f);
	float sr = sin(_roll * 0.5f);

	return
	{
		cr * cp * cy + sr * sp * sy,
		sr * cp * cy - cr * sp * sy,
		cr * sp * cy + sr * cp * sy,
		cr * cp * sy - sr * sp * cy
	};
}

// 行列に変換
Matrix4x4 Quaternion::ToMatrix() const
{
	return MatGenerateFunc::Rotate(*this);
}

// 球面補間
Quaternion Quaternion::Slerp(const Quaternion& _start, const Quaternion _end, float _t)
{
	float dot{ SIMDVectorMath::Dot4(_start.simd,_end.simd) };
	float theta{ acosf(dot) };

	// (sin((1-_t)θ) / sin(θ)_start + (sin(tθ) / sin(θ))_end

	float sinTheta{ sinf(theta) };
	// sin((1-_t)θ) / sin(θ)
	float weightStart{ sinf((1 - _t) * theta) / sinTheta };
	// sin(tθ) / sin(θ)
	float weightEnd{ sinf(_t * theta) / sinTheta };

	return
	{
		SIMDVectorMath::Add(
			SIMDVectorMath::MulScalar(_start.simd,weightStart), // (sin((1-_t)θ) / sin(θ)_start
			SIMDVectorMath::MulScalar(_end.simd,weightEnd)      // (sin(tθ) / sin(θ))_end
			)
	};
}


// 線形補間
Quaternion Lerp(const Quaternion& _start, const Quaternion _end, float _t)
{
	// start * ( 1 - t) + b * t
	return { SIMDVectorMath::Add(
		SIMDVectorMath::MulScalar(_start.simd,(1 - _t)),// start * ( 1 - t)
		SIMDVectorMath::MulScalar(_end.simd,_t)         // b * t
) };
}

// 内積
float Quaternion::Dot(const Quaternion& _rot1, const Quaternion& _rot2) const
{
	return SIMDVectorMath::Dot4(_rot1.simd, _rot2.simd);
}

Quaternion Quaternion::LookAt(const Vector3& _eye, const Vector3& _target, const Vector3& _up)
{
	Matrix4x4 m{ MatGenerateFunc::LookAt(_eye,_target,_up) };
	return
}