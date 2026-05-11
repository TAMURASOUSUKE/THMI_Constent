#pragma once
#include "SceneConstant/SceneConstant.h"
#include "../Object/Bases/ObjectManager.h"
#include "../Bases/SceneBase.h"

// 画面表示するデバッグ文字列の種類
enum class DebugString
{
	None = -1,
	Frame, // フレーム関連
	Input, // 入力関連
};

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

	void DebugFrameStrings(); // フレーム関連のデバッグ表示用文字列を集めた関数
	void DebugInputStrings(); // 入力関連のデバッグ表示用文字列を集めた関数

private:
	ObjectManager objManager{}; // オブジェクト管理用

	// デバッグ用
	DebugString currentDebugMode{ DebugString::None }; // 現在のデバッグ用文字列表示
	unsigned int debugRed{ GetColor(255, 0, 0) }; // デバッグ表示色 : 赤
	unsigned int debugWhite{ GetColor(255, 255, 255) }; // デバッグ表示色 : 白
	int debugStringPos{ 0 };
	int debugStringHeight{ 20 }; // 文字列表示時の行間

	
};