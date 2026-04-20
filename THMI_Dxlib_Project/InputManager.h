#pragma once
#include <array>
#include <string>
#include "GameConstant/GameKey.h"
#include "GameConstant/GameConstant.h"


// 入力管理を行うファイル
class InputManager
{
public:
	// シングルトン化
	static InputManager& Instance(); // インスタンスを取得する
	~InputManager() = default; // デフォルトデストラクタ

private:
	InputManager() = default; // コンストラクタはprivateに

private:
	const std::string configFilePath{ "Data/key_config.json" }; // コンフィグファイルへのパス

	InputMode currentMode{ InputMode::Game }; // 現在の入力状態を管理する

	int count{ 0 }; // 連続入力防止に使うカウンター
	int currentPadInput{ 0 }; // ゲームパッド
	int padTriggerDeadZone{ 0 }; // トリガーを押す深さ
	int prevMousePosX{ 0 }; // マウスのX座標
	int prevMousePosY{ 0 }; // マウスのY座標


};