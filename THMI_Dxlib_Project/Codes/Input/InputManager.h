#pragma once
#include <array>
#include <string>
#include <Dxlib.h>
#include "GameConstant/GameKey.h"
#include "SystemConstant/SystemConstant.h"
#include "../Math/Vector/Vector2/Vector2.h"

// 入力管理を行うファイル
class InputManager
{
public:
	// シングルトン化
	static InputManager& Instance(); // インスタンスを取得する
	~InputManager() = default; // デフォルトデストラクタ

	// 正規化された移動ベクトルを取得
	const Vector2& GetAxis() const;

	// 現在のカメラAxisを取得する
	const Vector2& GetCameraAxis() const;

	// 現在の入力状態を取得する
	const InputMode GetInputMode() const;

	// トリガ―を押す深さを取得する
	const int GetTriggerDeadZone() const;

	// Rスティックのデッドゾーンを取得
	const int GetStickDeadZone() const;

	// マウス感度を取得
	const float GetMouseSensibility() const;

	// スティック感度を取得
	const float GetStickSensibility() const;

	// 毎フレームの入力更新
	void Update();

	// Jsonへのキーコンフィグ保存
	void SaveConfig();

	// Jsonからのキーコンフィグ読み取り用
	void LoadConfig();

	// キーボードのみの入力設定
	void SetBindingKey(ActionID::GameAction _action, int _key);

	// キーボード設定関数をUIにオーバーロードしたもの
	void SetBidingKey(ActionID::UI _action, int _key);

	// アクションに二つ目のサブキーを追加(ゲーム操作状態)
	void AddKeyBinding(ActionID::GameAction _action, int _key);

	// アクションに二つ目のサブキーを追加(UI操作状態)
	void AddKeyBinding(ActionID::UI _action, int _key);

	// アクションに二つ目のサブボタンを追加(ゲーム操作状態)
	void AddButtonBinding(ActionID::GameAction _action, int _button);

	// アクションに二つ目のサブボタンを追加(UI操作状態)
	void AddButtonBinding(ActionID::UI _action, int _button);

	// パッドボタンのみの入力設定(ゲーム操作状態)
	void SetBindingPad(ActionID::GameAction _action, int _padMask);

	// パッドボタンのみの入力設定(UI操作状態)
	void SetBindingPad(ActionID::UI _action, int _padMask);

	// 現在の入力状態を変更する
	void SetInputMode(const InputMode _inputMode);

	// 押されたキーを返す
	int GetAnyPressedKey() const;

	// 押されたボタンを返す
	int GetAnyPressButton() const;

	// 入力判定
	bool GetButtonStay(ActionID::GameAction _key) const; // 押している間 : ゲーム中
	bool GetButtonStay(ActionID::UI _key) const; // 押している間 : UI中
	bool GetButtonDown(ActionID::GameAction _key) const; // 押した瞬間 : ゲーム中
	bool GetButtonDown(ActionID::UI _key) const; // 押した瞬間 : UI中
	bool GetButtonUp(ActionID::GameAction _key) const; // 離した瞬間 : ゲーム中
	bool GetButtonUp(ActionID::UI _key) const; // 離した瞬間 : UI中

private:
	InputManager(); // コンストラクタはprivateに

private:
	const std::string configFilePath{ "Data/key_config.json" }; // コンフィグファイルへのパス

	InputMode currentMode{ InputMode::Game }; // 現在の入力状態を管理する

	int count{ 0 }; // 連続入力防止に使うカウンター
	int currentPadInput{ 0 }; // ゲームパッド
	int padTriggerDeadZone{ 0 }; // トリガーを押す深さ
	int prevMousePosX{ 0 }; // マウスのX座標
	int prevMousePosY{ 0 }; // マウスのY座標
	int stickRDeadZone{ 5000 }; // Rスティックを動かすときのデッドゾーン
#ifdef _DEBUG
	int windowWidth{ DEBUG_WINDOW_WIDTH }; // 画面横幅(デバッグ時)
	int windowHeight{ DEBUG_WINDOW_HEIGHT }; // 画面縦幅(デバッグ時)
#else
	int windowWidth{ WINDOW_WIDTH }; // 画面横幅
	int windowHeight{ WINDOW_HEIGHT }; // 画面縦幅
#endif // _DEBUG

	float mosueSensibility{ 0.005f }; // マウス感度
	float stickSensibility{ 1.0f }; // スティック感度

	/*
		UI用のバインディングとゲーム用のバインディング配列を作成し
		それぞれで割り振る
	*/
	// Game用配列
	std::array<bool, static_cast<int>(ActionID::GameAction::Count)> currentGameState{}; // 現在の状態
	std::array<bool, static_cast<int>(ActionID::GameAction::Count)> prevGameStates; // 1フレーム前の状態
	std::array<InputBinding, static_cast<int>(ActionID::GameAction::Count)> gameBindings; //全アクションのマッピングデータ

	// UI用配列
	std::array<bool, static_cast<int>(ActionID::UI::Count)> currentUIStates; // 現在の状態
	std::array<bool, static_cast<int>(ActionID::UI::Count)> prevUIStates; // 1フレーム前の状態
	std::array<InputBinding, static_cast<int>(ActionID::UI::Count)> uiBindings; // 全アクションのマッピングデータ

	std::array<char, 256> currentKeyBuffer; // キーボード

	Vector2 axis{0.0f, 0.0f}; // スティックの値
	Vector2 cameraAxis{ 0.0f, 0.0f }; // カメラへの入力値

	XINPUT_STATE xinputState; // トリガー等を操作するためのXboxコントローラー対応型変数

};