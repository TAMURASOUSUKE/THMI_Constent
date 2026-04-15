#pragma once
#include <Dxlib.h>
#include "ObjectBase.h"



// 3D空間で存在するオブジェクトの基底となるクラス
class WorldObjectBase : public ObjectBase
{
public:
	// デフォルトコンストラクタ
	WorldObjectBase() = default;

	// デフォルトデストラクタ
	virtual ~WorldObjectBase() = default;


	// コンストラクタ群
	WorldObjectBase(const VECTOR& position) : position{ position }, ObjectBase(RenderLayer::World) {}
	WorldObjectBase(const VECTOR& position, const bool& isActive) : position{ position }, ObjectBase(isActive, RenderLayer::World) {}
	WorldObjectBase(const VECTOR& position, const VECTOR& rotation, const bool& isActive) : position{ position }, rotation{ rotation }, ObjectBase(isActive, RenderLayer::World) {}
	WorldObjectBase(const VECTOR& position, const VECTOR& rotation, const VECTOR& scale, const bool& isActive) : position{ position }, rotation{ rotation }, scale{ scale }, ObjectBase(isActive, RenderLayer::World) {}
	WorldObjectBase(const VECTOR& position, const VECTOR& rotation, const VECTOR& scale, const bool& isActive, const int& hanlde) : position{ position }, rotation{ rotation }, scale{ scale }, ObjectBase(isActive, RenderLayer::World, hanlde) {}

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