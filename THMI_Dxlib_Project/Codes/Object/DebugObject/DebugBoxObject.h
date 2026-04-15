#pragma once
#include <Dxlib.h>
#include "../Bases/WorldObjectBase.h"


// 描画と更新をテストするデバッグ用オブジェクト
class DebugBoxObject : public WorldObjectBase
{
public:
	DebugBoxObject() = default; // デフォルトコンストラクタ
	~DebugBoxObject() = default; // デフォルトデストラクタ

	DebugBoxObject(VECTOR _position, int _handle) :  WorldObjectBase(_position, _handle) { isActive = true; } // コンストラクタ

	void Update() override; // 更新
	void Draw() override; // 描画
private:
	unsigned int color{ GetColor(255, 255, 255) }; // オブジェクトが持つ色
};