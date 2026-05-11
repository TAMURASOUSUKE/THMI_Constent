#include <unordered_map>
#include <fstream>
#include "../nlohmann/json.hpp" // キーコンフィグ設定を保存するためのJsonを簡単に使えるようにするためのライブラリ
#include "InputManager.h"

using json = nlohmann::json; // 変数名省略

InputManager& InputManager::Instance()
{
	static InputManager instance;
	return instance;
}

// コンストラクタ
InputManager::InputManager()
{
	// 最初にデータをロードする
	LoadConfig();

	// fill = 指定した値で要素を埋める
	currentKeyBuffer.fill(0);
	currentGameStates.fill(false);
	currentUIStates.fill(false);
	prevGameStates.fill(false);
	prevUIStates.fill(false);

	// マウスの座標を最初に取得
	GetMousePoint(&prevMousePosX, &prevMousePosY);

	currentMode = InputMode::Game; // 最初にどのモードから始めるか
}

const Vector2& InputManager::GetAxis() const
{
	return axis;
}

const Vector2& InputManager::GetCameraAxis() const
{
	return cameraAxis;
}

const InputMode InputManager::GetInputMode() const
{
	return currentMode;
}

const int InputManager::GetTriggerDeadZone() const
{
	return padTriggerDeadZone;
}

const int InputManager::GetStickDeadZone() const
{
	return padStickRDeadZone;
}

const float InputManager::GetMouseSensibility() const
{
	return mouseSensibility;
}

const float InputManager::GetStickSensibility() const
{
	return padStickSensibility;
}

void InputManager::Update()
{
	// 前フレームの状態を保存
	prevGameStates = currentGameStates;
	prevUIStates = currentUIStates;

	GetHitKeyStateAll(currentKeyBuffer.data()); // 現在の入力状態を取得
	currentPadInput = GetJoypadInputState(DX_INPUT_PAD1); // パッドの現在の入力状態を取得
	GetJoypadXInputState(DX_INPUT_PAD1, &xinputState); // Triggerなどの状態を取得
	currentMouseInput = GetMouseInput(); // マウスの状態を取得

	// ボタン更新
	UpdateGameKey();

	// カメラ更新
	UpdateCameraInput();

	count++; // カウンターを増やす
}

// Jsonへのセーブ機能
void InputManager::SaveConfig()
{
	json root;

	// 全てのアクションをループさせJsonオブジェクトを作る
	// ゲーム内
	for (int i = 0; i < static_cast<int>(ActionID::GameAction::Count); i++)
	{
		ActionID::GameAction key{ static_cast<ActionID::GameAction>(i) }; // 現在の数をGameKey型へcastするためキャッシュ
		std::string keyName{ GameKeyToString(key) }; // GameKeyの名前を文字列型へ変換する

		// InputBindingの内容をJsonに詰める
		root["Game"][keyName] =
		{
			{"Keys", gameBindings[i].keyboardKeys}, // vectorは自動的に配列保存される
			{"Pad", gameBindings[i].padButtonMasks},
			{"Click", gameBindings[i].clickMasks},
		};
	}

	// ゲーム外
	for (int i = 0; i < static_cast<int>(ActionID::UI::Count); i++)
	{
		ActionID::UI key{ static_cast<ActionID::UI>(i) }; // 現在の数をGameKey型へcastするためキャッシュ
		std::string keyName{ UIKeyToString(key) }; // GameKeyの名前を文字列型へ変換する

		// InputBindingの内容をJsonに詰める
		root["UI"][keyName] =
		{
			{"Keys", uiBindings[i].keyboardKeys}, // vectorは自動的に配列保存される
			{"Pad", uiBindings[i].padButtonMasks},
			{"Click", uiBindings[i].clickMasks},
		};
	}

	// LTRTを押す深さをキーコンフィグから設定できるようにする
	root["TriggerDeadZone"] = padTriggerDeadZone;
	// マウス感度をキーコンフィグから設定できるようにする
	root["MouseSensibility"] = mouseSensibility;
	// 右スティック感度をキーコンフィグ設定からできるようにする
	root["RightStickSensibility"] = padStickSensibility;
	// スティックのデッドゾーンをキーコンフィグから設定できるようにする
	root["RightStickDeadZone"] = padStickRDeadZone;

	// ファイル書き出し
	std::ofstream file{ configFilePath };
	if (file.is_open())
	{
		file << root.dump(4);
		file.close();
	}
}

// ファイルの読み取り
void InputManager::LoadConfig()
{
	std::ifstream file{ configFilePath };

	// ファイルが開けない場合はデフォルト設定を使う
	if (!file.is_open())
	{
		SetDefaultBindings(); // 初期設定
		SaveConfig(); // セーブ
		return;
	}

	// Jsonが破損等開けない理由があった場合対応するためtry-catchを使う
	try
	{
		json root; 
		file >> root;

		// Gameを読み込む
		if (root.contains("Game"))
		{
			// Json中身を解析してbindingにセット
			for (auto& element : root["Game"].items())
			{
				std::string keyName{ element.key() }; // Jump等のアクション名
				ActionID::GameAction key{ StringToGameKey(keyName) }; // Enumに変換する

				// 無効なキーならスキップ
				if (static_cast<int>(key) < 0) continue;

				int index{ static_cast<int>(key) }; // GameKey型をindexに変換する

				// 値を取り出す
				gameBindings[index].keyboardKeys = element.value()["keys"].get<std::vector<int>>(); // キーボード
				gameBindings[index].padButtonMasks = element.value()["pad"].get<std::vector<int>>(); // ボタン
				gameBindings[index].clickMasks = element.value()["click"].get <std::vector<int>>(); // クリック
			}
		}

		// UIを読み込む
		if (root.contains("UI"))
		{
			for (auto& element : root["UI"].items())
			{
				std::string keyName{ element.key() }; // アクション名をキャッシュ
				ActionID::UI key{StringToUIKey(keyName)}; // Enumに変換する

				if (static_cast<int>(key)) continue;

				int index{ static_cast<int>(key) }; // UI型をintへキャッシュ

				uiBindings[index].keyboardKeys = element.value()["keys"].get<std::vector<int>>(); // int型配列として取得
				uiBindings[index].padButtonMasks = element.value()["pad"].get<std::vector<int>>(); // int型配列として取得
				uiBindings[index].clickMasks = element.value()["click"].get <std::vector<int>>(); // int型配列として取得
			}
		}

		// トリガーの深さ設定があるかどうか確認して読み込む
		if (root.contains("TriggerDeadZone"))
		{
			padTriggerDeadZone = root["TriggerDeadZone"].get<int>();
		}
		// マウス感度があるかどうかをチェックしてから取り込む
		if (root.contains("MouseSensibility"))
		{
			mouseSensibility = root["MouseSensibility"].get<float>();
		}
		// 右スティック感度があるかどうかをチェックしてから取り込む
		if (root.contains("RightStickSensibility"))
		{
			padStickSensibility = root["RightStickSensibility"].get<float>();
		}
		// 右スティックデッドゾーンがあるかどうかをチェックして取り込む
		if (root.contains("RightStickDeadZone"))
		{
			padStickRDeadZone = root["RightStickDeadZone"].get<int>();
		}
	}
	catch(const std::exception& e)
	{
		// Jsonが壊れていた場合にはデフォルトに戻す
		SetDefaultBindings();
	}

}

// キーボードの入力設定(ゲームアクション)
void InputManager::SetBindingKey(ActionID::GameAction _action, int _key)
{
	int index{ static_cast<int>(_action) }; // インデック用キャッシュ

	// 既存のキーをリセットして新しい物を登録
	gameBindings[index].keyboardKeys.clear(); // リセット
	gameBindings[index].keyboardKeys.push_back(_key);
}

// キーボードの入力設定(UI操作)
void InputManager::SetBindingKey(ActionID::UI _action, int _key)
{
	int index{ static_cast<int>(_action) }; // インデック用キャッシュ

	// 既存のキーをリセットして新しい物を登録
	uiBindings[index].keyboardKeys.clear(); // リセット
	uiBindings[index].keyboardKeys.push_back(_key);
}

// 二つ目のサブキー(ゲームアクション)
void InputManager::AddKeyBinding(ActionID::GameAction _action, int _key)
{
	int index{ static_cast<int>(_action) }; // インデックスのキャッシュ
	gameBindings[index].keyboardKeys.push_back(_key);
}

// 二つ目のサブキー(UI操作中)
void InputManager::AddKeyBinding(ActionID::UI _action, int _key)
{
	int index{ static_cast<int>(_action) }; // インデックスのキャッシュ
	uiBindings[index].keyboardKeys.push_back(_key);
}

// ボタンの入力設定
void InputManager::SetBindingPad(ActionID::GameAction _action, int _padMask)
{
	int index{ static_cast<int>(_action) };

	gameBindings[index].padButtonMasks.clear(); // リセット
	gameBindings[index].padButtonMasks.push_back(_padMask);
}

// UI操作中のボタンの入力設定
void InputManager::SetBindingPad(ActionID::UI _action, int _padMask)
{
	int index{ static_cast<int>(_action) };

	uiBindings[index].padButtonMasks.clear(); // リセット
	uiBindings[index].padButtonMasks.push_back(_padMask);
}

// 二つ目のサブボタン(ゲームアクション)
void InputManager::AddButtonBinding(ActionID::GameAction _action, int _button)
{
	// サブボタンをセットする
	int index{ static_cast<int>(_action) };
	gameBindings[index].keyboardKeys.push_back(_button);
}

// 二つ目のサブボタン(UI操作中)
void InputManager::AddButtonBinding(ActionID::UI _action, int _button)
{
	// サブボタンをセットする
	int index{ static_cast<int>(_action) };
	uiBindings[index].padButtonMasks.push_back(_button);
}

// ゲーム中のマウスクリックの設定
void InputManager::SetBindingMouse(ActionID::GameAction _action, int _mouseButton)
{
	int index{ static_cast<int>(_action) };

	gameBindings[index].clickMasks.clear(); // リセット
	gameBindings[index].clickMasks.push_back(_mouseButton);
}

// UI操作中のマウスクリックの設定
void InputManager::SetBindingMouse(ActionID::UI _action, int _mouseButton)
{
	int index{ static_cast<int>(_action) };

	uiBindings[index].clickMasks.clear(); // リセット
	uiBindings[index].clickMasks.push_back(_mouseButton);
}

// ゲーム中のクリックのサブ設定
void InputManager::AddMouseBinding(ActionID::GameAction _action, int _mouseButton)
{
	// サブボタンをセットする
	int index{ static_cast<int>(_action) };
	gameBindings[index].clickMasks.push_back(_mouseButton);
}

// UI操作中のクリックのサブ設定
void InputManager::AddMouseBinding(ActionID::UI _action, int _mouseButton)
{
	// サブボタンをセットする
	int index{ static_cast<int>(_action) };
	uiBindings[index].clickMasks.push_back(_mouseButton);
}

// モードの設定
void InputManager::SetInputMode(const InputMode _inputMode)
{
	if (currentMode == _inputMode) return; // 同じなら何もしない
	currentMode = _inputMode;

	prevGameStates = currentGameStates;
	prevUIStates = currentUIStates;
}

// 押されたキーを返す
int InputManager::GetAnyPressedKey() const
{
	for (int i = 0; i < currentKeyBuffer.size(); i++)
	{
		// 全キーを精査して押された瞬間のものがあればその番号を返す
		if (currentKeyBuffer[i] == 1)
		{
			return i;
		}
	}

	return -1; // 何も押されていなければ-1
}

// 押されたボタンを返す
int InputManager::GetAnyPressedButton() const
{
	// 調べるボタンをまとめたリスト(トリガー以外)
	int checkButttons[]{
		PadCode::NORTH,
		PadCode::SOUTH,
		PadCode::EAST,
		PadCode::WEST,
		PadCode::STICK_CLICK_L,
		PadCode::STICK_CLICK_R,
		PadCode::SHOULDER_L,
		PadCode::SHOULDER_R,
	};


	// トリガー以外の全てのキーと現状の入力されているボタンを&演算し1が返ってきたボタンを戻り値とする
	for (int button : checkButttons)
	{
		if ((button & currentPadInput) != 0)
		{
			return button;
		}
	}

	// トリガー判定
	if (xinputState.LeftTrigger > padTriggerDeadZone)
	{
		return PadCode::TRIGGER_L;
	}

	if (xinputState.RightTrigger > padTriggerDeadZone)
	{
		return PadCode::TRIGGER_R;
	}

	return 0; // 見当たらなかったら0

}


void InputManager::UpdateGameKey()
{

	UpdateState(gameBindings, currentGameStates, static_cast<int>(ActionID::GameAction::Count)); // ゲーム中
	UpdateState(uiBindings, currentUIStates, static_cast<int>(ActionID::UI::Count)); // UI操作中

	// Axisに関してはゲーム内のみなのdえUIは行わなくて良い
	auto Index = [](ActionID::GameAction _key) { return static_cast<int>(_key); };

	// 初期化
	axis = Vector2::ZERO;

	// スティック処理
	float stickX = static_cast<float>(xinputState.ThumbLX);
	float stickY = static_cast<float>(xinputState.ThumbLY);

	// デッドゾーン処理(少し倒した状態なら無視するようにする)
	if (std::abs(stickX) < padStickRDeadZone) stickX = 0.0f;
	if (std::abs(stickY) < padStickRDeadZone) stickY = 0.0f;

	// sitc変数をVector2にまとめつつ値を-1.0～1.0まで丸める
	Vector2 stick{ stickX / MAX_XINPUT_VALUE, stickY / MAX_XINPUT_VALUE };
	axis += stick * padStickSensibility;

	// 移動ベクトル作成
	if (currentGameStates[Index(ActionID::GameAction::Up)]) axis.y += 1.0f;
	if (currentGameStates[Index(ActionID::GameAction::Down)]) axis.y -= 1.0f;
	if (currentGameStates[Index(ActionID::GameAction::Right)]) axis.x += 1.0f;
	if (currentGameStates[Index(ActionID::GameAction::Left)]) axis.x -= 1.0f;

	// 0ベクトル対策つき正規化
	float lenSq = axis.x * axis.x + axis.y * axis.y;

	if (lenSq > 0.0001f)
	{
		axis.Normalize();
	}
	else
	{
		axis = Vector2::ZERO;
	}
}

void InputManager::UpdateCameraInput()
{
	if (currentMode != InputMode::Game) return; // ゲーム中でないなら計算しない

	cameraAxis = Vector2::ZERO; // 毎フレームリセット

	// マウス処理
	int mouseX;
	int mouseY;

	// 現在の位置を取得
	GetMousePoint(&mouseX, &mouseY);

	// 移動量を現在 - 過去で求める
	Vector2 delta{static_cast<float>(mouseX - prevMousePosX), -static_cast<float>(mouseY - prevMousePosY)};

	// 感度を考慮し計算
	cameraAxis = delta * mouseSensibility;

	// 現在位置を保存
	prevMousePosX = mouseX;
	prevMousePosY = mouseY;

	// 右スティック処理
	float stickX{ static_cast<float>(xinputState.ThumbRX) };
	float stickY{ static_cast<float>(xinputState.ThumbRY) };

	// デッドゾーン処理(少し倒した状態なら無視とする)
	if (std::abs(stickX) < padStickRDeadZone) stickX = 0.0f;
	if (std::abs(stickY) < padStickRDeadZone) stickY = 0.0f;

	// static変数をVector2にまとめつつ値を-1.0 ～ 1.0までまとめる
	Vector2 stick{ stickX / MAX_XINPUT_VALUE, stickY / MAX_XINPUT_VALUE };

	// 実際の加算
	cameraAxis += stick * padStickSensibility;

	// マウスカーソルを画面中央固定
	if (GetMainWindowHandle() == GetForegroundWindow()) // ウィンドウがアクティブな時だけ
	{
		Vector2Int center{ windowWidth / 2, windowHeight / 2 };

		// 画面中央に戻す
		SetMousePoint(center.x, center.y);

		// 移動量が爆増するのでprevMousePosを更新することで避ける
		prevMousePosX = center.x;
		prevMousePosY = center.y;
	}
}

// 押している間
bool InputManager::GetButtonStay(ActionID::GameAction _key) const
{
	if (currentMode != InputMode::Game) return false; // 現在の状態がGameでなかったら反応しないようにする
	return currentGameStates[static_cast<int>(_key)];
}

bool InputManager::GetButtonStay(ActionID::UI _key) const
{
	if (currentMode != InputMode::Menu) return false; // 現在の状態がGameでなかったら反応しないようにする
	return currentUIStates[static_cast<int>(_key)];
}

// 押した瞬間
bool InputManager::GetButtonDown(ActionID::GameAction _key) const
{
	if (currentMode != InputMode::Game) return false; // 現在の状態がGameでなかったら反応しないようにする
	int index{ static_cast<int>(_key) }; // Enumをキャストしてキャッシュする
	return currentGameStates[index] && !prevGameStates[index]; // 前フレームではfalse現フレームtrue
}

bool InputManager::GetButtonDown(ActionID::UI _key) const
{
	if (currentMode != InputMode::Menu) return false; // 現在の状態がGameでなかったら反応しないようにする
	int index{ static_cast<int>(_key) }; // Enumをキャストしてキャッシュする
	return currentUIStates[index] && !prevUIStates[index]; // 前フレームではfalse現フレームtrue
}

// 離した瞬間
bool InputManager::GetButtonUp(ActionID::GameAction _key) const
{
	if (currentMode != InputMode::Game) return false; // 現在の状態がGameでなかったら反応しないようにする
	int index{ static_cast<int>(_key) }; // インデックスをキャスト
	return !currentGameStates[index] && prevGameStates[index]; // 現フレームでは離しており前フレームでは離していない
}

bool InputManager::GetButtonUp(ActionID::UI _key) const
{
	if (currentMode != InputMode::Menu) return false; // 現在の状態がGameでなかったら反応しないようにする
	int index{ static_cast<int>(_key) }; // インデックスをキャスト
	return !currentUIStates[index] && prevUIStates[index]; // 現フレームでは離しており前フレームでは離していない
}




void InputManager::UpdateState(const auto& _bindingsArray, auto& _stateArray, int _count)
{
	// 全探索を行う
	for (int i = 0; i < _count; i++)
	{
		const auto& binding{ _bindingsArray[i] }; // 現在のキーをキャッシュする
		bool isDown{ false }; // 押されたか判定する

		// パッド判定
		for (int button : binding.padButtonMasks)
		{
			// trigger判定
			/*
				currentPadInputにはTriggerの情報は含まれていないため
				設定されているマスクそのものと比較する必要がある
			*/
			// 左
			if (button == PadCode::TRIGGER_L)
			{
				/*
					XBoxコントローラーはTriggerがアナログ式のため
					取得値をデッドゾーンで比較するが
					任天堂のプロコン等はZRやZLがデジタルボタンなので0,1で評価する
				*/
				if (xinputState.LeftTrigger > padTriggerDeadZone)
				{
					isDown = true;
				}
				else if ((currentPadInput & PadCode::TRIGGER_L) != 0)
				{
					isDown = true;
				}
			}
			// 右
			else if (button == PadCode::TRIGGER_R)
			{
				// XBox
				if (xinputState.RightTrigger > padTriggerDeadZone)
				{
					isDown = true;
				}
				// switchプロコンなど
				else if ((currentPadInput & PadCode::TRIGGER_R) != 0)
				{
					isDown = true;
				}
			}
			// それ以外のパッドのボタン判定
			else if ((currentPadInput & button) != 0)
			{
				isDown = true;
			}
		}

		// クリック判定
		if (!isDown)
		{
			for (int mouse : binding.clickMasks)
			{
				// 何かが押されていればtrue
				if ((currentMouseInput & mouse) != 0)
				{
					isDown = true;
					break;
				}
			}
		}

		// まだ押されていなかったらキーボードを判定する
		if (!isDown)
		{
			// キーボード判定
			for (int key : binding.keyboardKeys)
			{
				// 配列外例外参照
				if (key >= 0 && key < 256)
				{
					if (currentKeyBuffer[key] != 0)
					{
						isDown = true;
						break; // 一つでも押されていれば抜ける
					}
				}
			}
		}

		_stateArray[i] = isDown; // 最終的な状態決定
	}
}

// キーのデフォルト割り当て
void InputManager::SetDefaultBindings()
{
	SetBindingKey(ActionID::GameAction::Up, KEY_INPUT_W);
	SetBindingKey(ActionID::GameAction::Down, KEY_INPUT_S);
	SetBindingKey(ActionID::GameAction::Right, KEY_INPUT_D);
	SetBindingKey(ActionID::GameAction::Left, KEY_INPUT_A);
	SetBindingKey(ActionID::GameAction::Avoid, KEY_INPUT_SPACE);

	SetBindingKey(ActionID::UI::Up, KEY_INPUT_W);
	SetBindingKey(ActionID::UI::Down, KEY_INPUT_S);
	SetBindingKey(ActionID::UI::Right, KEY_INPUT_D);
	SetBindingKey(ActionID::UI::Left, KEY_INPUT_A);
	SetBindingKey(ActionID::UI::Decide, KEY_INPUT_E);
	SetBindingKey(ActionID::UI::Cancel, KEY_INPUT_Q);
	SetBindingKey(ActionID::UI::Pause, KEY_INPUT_ESCAPE);

	SetBindingPad(ActionID::GameAction::Up, PadCode::UP);
	SetBindingPad(ActionID::GameAction::Down, PadCode::DOWN);
	SetBindingPad(ActionID::GameAction::Right, PadCode::RIGHT);
	SetBindingPad(ActionID::GameAction::Left, PadCode::LEFT);
	SetBindingPad(ActionID::GameAction::Attack, PadCode::WEST);
	SetBindingPad(ActionID::GameAction::Avoid, PadCode::SOUTH);

	SetBindingPad(ActionID::UI::Up, PadCode::UP);
	SetBindingPad(ActionID::UI::Down, PadCode::DOWN);
	SetBindingPad(ActionID::UI::Right, PadCode::RIGHT);
	SetBindingPad(ActionID::UI::Left, PadCode::LEFT);
	SetBindingPad(ActionID::UI::Decide, PadCode::EAST);
	SetBindingPad(ActionID::UI::Cancel, PadCode::SOUTH);
	SetBindingPad(ActionID::UI::Pause, PadCode::START);
	SetBindingPad(ActionID::GameAction::Up, PadCode::UP);

	SetBindingMouse(ActionID::GameAction::Attack, ClickCode::LEFT);
	SetBindingMouse(ActionID::UI::Decide, ClickCode::LEFT);

	// サブキー
	AddKeyBinding(ActionID::GameAction::Up, KEY_INPUT_UP);
	AddKeyBinding(ActionID::GameAction::Down, KEY_INPUT_DOWN);
	AddKeyBinding(ActionID::GameAction::Right, KEY_INPUT_RIGHT);
	AddKeyBinding(ActionID::GameAction::Left, KEY_INPUT_LEFT);

	// UI
	AddKeyBinding(ActionID::UI::Up, KEY_INPUT_UP);
	AddKeyBinding(ActionID::UI::Down, KEY_INPUT_DOWN);
	AddKeyBinding(ActionID::UI::Right, KEY_INPUT_RIGHT);
	AddKeyBinding(ActionID::UI::Left, KEY_INPUT_LEFT);
	AddButtonBinding(ActionID::UI::Pause, PAD_INPUT_M); // Xboxのスタートボタンを登録

	// トリガーを押す深さ
	padTriggerDeadZone = DEFAULT_TRIGGER_DEAD_ZONE; // 最初はデフォルトを入れておく
	// 右スティックのデッドゾーン
	padStickRDeadZone = DEFAULT_STICK_DEAD_ZONE;
	// マウス感度
	mouseSensibility = DEFAULT_MOUSE_SENSIBILITY;
	// スティック感度
	padStickSensibility = DEFAULT_STICK_SENSIBILITY;
}

// GameKey型から文字列へ
std::string InputManager::GameKeyToString(ActionID::GameAction _key)
{
	switch (_key)
	{
	case ActionID::GameAction::Up: return "Up";
	case ActionID::GameAction::Down: return "Down";
	case ActionID::GameAction::Right: return "Right";
	case ActionID::GameAction::Left: return "Left";
	case ActionID::GameAction::Attack: return "Attack";
	case ActionID::GameAction::Avoid: return "Avoid";
	default: return "Unknown";
	}
}

std::string InputManager::UIKeyToString(ActionID::UI _key)
{
	switch (_key)
	{
	case ActionID::UI::Up: return "Up";
	case ActionID::UI::Down: return "Down";
	case ActionID::UI::Left: return "Left";
	case ActionID::UI::Right: return "Right";
	case ActionID::UI::Decide: return "Decide";
	case ActionID::UI::Cancel: return "Cancel";
	case ActionID::UI::Pause: return "Pause";
	default: return "Unknown";
	}
}

// 文字列からGameKey型へ
ActionID::GameAction InputManager::StringToGameKey(const std::string& _str)
{
	if (_str == "Up") return ActionID::GameAction::Up;
	if (_str == "Down") return ActionID::GameAction::Down;
	if (_str == "Left") return ActionID::GameAction::Left;
	if (_str == "Right") return ActionID::GameAction::Right;
	if (_str == "Attack") return ActionID::GameAction::Attack;
	return static_cast<ActionID::GameAction>(-1); // エラー用に用意
}

ActionID::UI InputManager::StringToUIKey(const std::string& _str)
{
	if (_str == "Up") return ActionID::UI::Up;
	if (_str == "Down") return ActionID::UI::Down;
	if (_str == "Left") return ActionID::UI::Left;
	if (_str == "Right") return ActionID::UI::Right;
	if (_str == "Decide") return ActionID::UI::Decide;
	if (_str == "Cancel") return ActionID::UI::Cancel;
	if (_str == "Pause") return ActionID::UI::Pause;
	return static_cast<ActionID::UI>(-1); // エラー用
}