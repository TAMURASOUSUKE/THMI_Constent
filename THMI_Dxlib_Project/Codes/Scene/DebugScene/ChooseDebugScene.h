#pragma once
#include "SceneConstant/SceneConstant.h"
#include "../Bases/SceneBase.h"

// デバッグシーンを選択する際に選びやすくするためのシーン
class ChooseDebugScene : public SceneBase
{
public:
	ChooseDebugScene() = default;
	~ChooseDebugScene() = default;

	// 描画
	void Draw() override;
	// シーンの種類を取得する関数
	SceneType GetType() override { return SceneType::ChooseDebug; }

private:
	void Initialize() override; // 最初に行う処理
	void Execute() override; // 実行処理
	void FixedExecute() override; // 固定更新処理
	SceneType Terminate() override; // シーンを抜ける際の処理
};