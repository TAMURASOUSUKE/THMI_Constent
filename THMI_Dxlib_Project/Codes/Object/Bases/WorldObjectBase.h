#pragma once
#include <Dxlib.h>
#include "ObjectBase.h"



// 3D空間で存在するオブジェクトの基底となるクラス
class WorldObjectBase : public ObjectBase
{
public:
    // デフォルトコンストラクタ
	WorldObjectBase() : ObjectBase(RenderLayer::World) {}

	// デフォルトデストラクタ
	virtual ~WorldObjectBase() = default;


	// コンストラクタ群

	// トランスフォーム系のみ初期化
	WorldObjectBase(const VECTOR& _position) : position{ _position }, ObjectBase(RenderLayer::World) {} // 位置のみ初期化
	WorldObjectBase(const VECTOR& _position, const VECTOR& _rotation) : position{ _position }, rotation{ _rotation }, ObjectBase(RenderLayer::World) {} //　位置と回転を初期化
	WorldObjectBase(const VECTOR& _position, const VECTOR& _rotation, const VECTOR& _scale) : position{ _position }, rotation{ _rotation }, scale{ _scale }, ObjectBase(RenderLayer::World) {} // 位置と回転とスケールの初期化

	// トランスフォーム系 + 生存フラグ初期化
	WorldObjectBase(const VECTOR& _position, const bool& _isActive) : position{ _position }, ObjectBase(_isActive, RenderLayer::World) {} // 位置と生存フラグを初期化
	WorldObjectBase(const VECTOR& _position, const VECTOR& _rotation, const bool& _isActive) : position{ _position }, rotation{ _rotation }, ObjectBase(_isActive, RenderLayer::World) {} // 位置と回転と生存フラグを初期化
	WorldObjectBase(const VECTOR& _position, const VECTOR& _rotation, const VECTOR& _scale, const bool& _isActive) : position{ _position }, rotation{ _rotation }, scale{ _scale }, ObjectBase(_isActive, RenderLayer::World) {} // 位置と回転とスケールと生存フラグを初期化

	// トランスフォーム系 + ハンドルを初期化
	WorldObjectBase(const VECTOR& _position, const int& _handle) : position{ _position }, ObjectBase(_handle, RenderLayer::World) {} // 位置とハンドル初期化
	WorldObjectBase(const VECTOR& _position, const VECTOR& _rotation, const int& _handle) : position{ _position }, rotation{ _rotation }, ObjectBase(_handle, RenderLayer::World) {} // 位置と回転とハンドルを初期化
	WorldObjectBase(const VECTOR& _position, const VECTOR& _rotation, const VECTOR& _scale, const int& _handle) : position{ _position }, rotation{ _rotation }, scale{ _scale }, ObjectBase(_handle, RenderLayer::World) {} // 位置と回転とスケールとハンドルを初期化

	// トランスフォーム系 + 生存フラグ + ハンドルを初期化
	WorldObjectBase(const VECTOR& _position, const bool& _isActive, const int& _handle) : position{ _position }, ObjectBase(_handle, _isActive, RenderLayer::World) {} // 位置と生存フラグとハンドルを初期化
	WorldObjectBase(const VECTOR& _position, const VECTOR& _rotation, const bool& _isActive, const int& _handle) : position{ _position }, rotation{ _rotation }, ObjectBase(_handle, _isActive, RenderLayer::World) {} // 位置と回転と生存フラグとハンドルを初期化
    WorldObjectBase(const VECTOR& _position, const VECTOR& _rotation, const VECTOR& _scale, const bool& _isActive, const int& _handle) : position{ _position }, rotation{ _rotation }, scale{ _scale }, ObjectBase(_handle, _isActive, RenderLayer::World) {} // 位置と回転とスケールと生存フラグとハンドルを初期化

	// 固定更新
	virtual void FixedUpdate() {}

	// 位置のGetter
	const VECTOR& GetPosition() const noexcept { return position; }

	// 回転のGetter
	const VECTOR& GetRotation() const noexcept { return rotation; }

	// 大きさのGetter
	const VECTOR& GetScale() const noexcept { return scale; }

protected:

	VECTOR position{ 0.0f, 0.0f, 0.0f };
	VECTOR rotation{ 0.0f, 0.0f, 0.0f };
	VECTOR scale{ 1.0f, 1.0f, 1.0f };

	VECTOR velocity{ 0.0f, 0.0f, 0.0f };
	VECTOR acceleration{ 0.0f, 0.0f, 0.0f };

};