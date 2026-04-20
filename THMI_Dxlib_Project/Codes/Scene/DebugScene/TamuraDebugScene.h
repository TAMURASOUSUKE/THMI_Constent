#pragma once
#include "SceneConstant/SceneConstant.h"
#include "../Object/Bases/ObjectManager.h"
#include "../Bases/SceneBase.h"

// 田村用デバッグシーンの機能提供
class TamuraDebugScene : public SceneBase
{
public:
	TamuraDebugScene() = default;
	~TamuraDebugScene();

	// 描画
	void Draw() override;
	// シーンの種類を取得する関数
	SceneType GetType() override { return SceneType::Tamura; }

private:
	void Initialize() override; // 最初に行う処理
	void Execute() override; // 実行処理
	void FixedExecute() override; // 固定更新処理
	SceneType Terminate() override; // シーンを抜ける際の処理

	void DebugDrawStrings(); // デバッグ表示用文字列を集めた関数

private:
	ObjectManager objManager{}; // オブジェクト管理用

	// デバッグ用
	unsigned int debugRed{ GetColor(255, 0, 0) }; // デバッグ表示色 : 赤
	unsigned int debugWhite{ GetColor(255, 255, 255) }; // デバッグ表示色 : 白
	int debugStringPos{ 0 };
	int debugStringHeight{ 20 }; // 文字列表示時の行間
};