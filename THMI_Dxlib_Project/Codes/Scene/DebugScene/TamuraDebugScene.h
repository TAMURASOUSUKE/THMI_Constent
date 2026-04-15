#pragma once
#include "SceneConstant/SceneConstant.h"
#include "../Object/Bases/ObjectManager.h"
#include "../Bases/SceneBase.h"

// 田村用デバッグシーンの機能提供
class TamuraDebugScene : public SceneBase
{
public:
	TamuraDebugScene() = default;
	~TamuraDebugScene() = default;

	// 描画
	void Draw() override;
	// シーンの種類を取得する関数
	SceneType GetType() override { return SceneType::Tamura; }

private:
	void Initialize() override; // 最初に行う処理
	void Execute() override; // 実行処理
	void FixedExecute() override; // 固定更新処理
	SceneType Terminate() override; // シーンを抜ける際の処理

private:
	ObjectManager objManager{}; // オブジェクト管理用
};