#pragma once

#include "../Matrix/Matrix.h"

struct alignas(16) Quaternion
{
public:
	union
	{
		struct
		{
			float x, y, z, w;
		};

		SIMDVectorFloat simd;
	};

	// 単位
	static Quaternion Identity();

	// 正規化
	Quaternion& Normalized();
	// 正規化
	Quaternion& Normalize();
	// 正規化
	static Quaternion& Normalized();
	// 正規化
	static Quaternion& Normalize();

	// 乗法
	Quaternion operator*(const Quaternion& _value) const;

	// 乗法
	Quaternion operator*=(const Quaternion& _value);

	// 逆数
	Vector3 Inverse() const;

	// 共役
	Quaternion Conjugate()const;

	// 軸と角とで回転
	static Quaternion AngleAxis(float _angle, Vector3& _axis);
	// オイラー角から生成
	static Quaternion Euler(float _pitch, float _yaw, float _roll);
	// 行列に変換
	Matrix4x4 ToMatrix() const;

	/// <summary>
	/// 球面補間
	/// </summary>
	/// <param name="_rot1">スタート</param>
	/// <param name="_rot2">ゴール</param>
	/// <param name="_t">時間(0～1)</param>
	/// <returns></returns>
	static Quaternion Slerp(const Quaternion& _rot1, const Quaternion _rot2, float _t);

	/// <summary>
	/// 線形補間
	/// </summary>
	/// <param name="_rot1">スタート</param>
	/// <param name="_rot2">ゴール</param>
	/// <param name="_t">時間(0～1)</param>
	/// <returns></returns>
	static Quaternion Lerp(const Quaternion& _rot1, const Quaternion _rot2, float _t);

	// 内積
	float Dot(const Quaternion& _rot1,const Quaternion& _rot2) const;
};