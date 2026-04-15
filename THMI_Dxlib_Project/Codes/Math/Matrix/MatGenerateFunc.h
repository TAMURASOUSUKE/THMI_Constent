#pragma once

#include "Matrix.h"
#include "../Quaternion/Quaternion.h"

namespace MatGenerateFunc
{
	Matrix4x4 Translate(const Vector3& _vec);
	Matrix4x4 Scale(const Vector3& _scale);
	Matrix4x4 Rotate(const Quaternion& _rot);
	Matrix4x4 RotateX(float _x);
	Matrix4x4 RotateY(float _y);
	Matrix4x4 RotateZ(float _z);
	Matrix4x4 TRS(const Vector3& _vec, const Quaternion& _rot, const Vector3& _scale);
	Matrix4x4 LookAt(const Vector3& eye, const Vector3& target, const Vector3& up);
}