//#include <unordered_map>
//#include <fstream>
//#include "../nlohmann/json.hpp" // キーコンフィグ設定を保存するためのJsonを簡単に使えるようにするためのライブラリ
//#include "InputManager.h"
//
//using json = nlohmann::json; // 変数名省略
//
//InputManager& InputManager::Instance()
//{
//	static InputManager instance;
//	return instance;
//}
//
//// コンストラクタ
//InputManager::InputManager()
//{
//	// 最初にデータをロードする
//	LoadConfig();
//
//	// fill = 指定した値で要素を埋める
//	currentKeyBuffer.fill(0);
//	currentGameStates.fill(false);
//	currentUIStates.fill(false);
//	prevGameStates.fill(false);
//	prevUIStates.fill(false);
//
//	// マウスの座標を最初に取得
//	GetMousePoint(&prevMousePosX, &prevMousePosY);
//
//	currentMode = InputMode::Game; // 最初にどのモードから始めるか
//}
//
//
//void InputManager::Update()
//{
//	// 前フレームの状態を保存
//	prevGameStates = currentGameStates;
//
//	GetHitKeyStateAll(currentKeyBuffer.data()); // 現在の入力状態を取得
//	currentPadInput = GetJoypadInputState(DX_INPUT_PAD1); // パッドの現在の入力状態を取得
//	GetJoypadXInputState(DX_INPUT_PAD1, &xinputState); // Triggerなどの状態を取得
//
//	// ボタン更新
//	UpdateGameKey();
//
//	// カメラ更新
//	UpdateCameraInput();
//
//	count++; // カウンターを増やす
//}
//
//void InputManager::UpdateGameKey()
//{
//	/*
//		ラムダを使って共通処理をまとめる
//		第一引数 : 設定したキーコンの配列
//		第二引数 : キーやボタンが押されているかが格納された配列
//		第三引数 : 要素数
//	*/
//
//	auto UpdateState = [&](const auto& _bindingsArray, auto& _stateArray, int _count)
//		{
//			// 全探索を行う
//			for (int i = 0; i < count; i++)
//			{
//				const auto& binding{ _bindingsArray[i] }; // 現在のキーをキャッシュする
//				bool isDown{ false }; // 押されたか判定する
//
//				// パッド判定
//				for (int button : binding.padButtonMasks)
//				{
//					// trigger判定
//					/*
//						currentPadInputにはTriggerの情報は含まれていないため
//						設定されているマスクそのものと比較する必要がある
//					*/
//					// 左
//					if (button == PadCode::TRIGGER_L)
//					{
//						/*
//							XBoxコントローラーはTriggerがアナログ式のため
//							取得値をデッドゾーンで比較するが
//							任天堂のプロコン等はZRやZLがデジタルボタンなので0,1で評価する
//						*/
//						if (xinputState.LeftTrigger > padTriggerDeadZone)
//						{
//							isDown = true;
//						}
//						else if ((currentPadInput & PadCode::TRIGGER_L) != 0)
//						{
//							isDown = true;
//						}
//					}
//					// 右
//					else if (button == PadCode::TRIGGER_R)
//					{
//						// XBox
//						if (xinputState.RightTrigger > padTriggerDeadZone)
//						{
//							isDown = true;
//						}
//						// switchプロコンなど
//						else if ((currentPadInput & PadCode::TRIGGER_R) != 0)
//						{
//							isDown = true;
//						}
//					}
//					// それ以外のパッドのボタン判定
//					else if ((currentPadInput & button) != 0)
//					{
//						isDown = true;
//					}
//				}
//
//				// まだ押されていなかったらキーボードを判定する
//				if (!isDown)
//				{
//					// キーボード判定
//					for (int key : binding.keyboardKeys)
//					{
//						// 配列外例外参照
//						if (key >= 0 && key < 256)
//						{
//							if (currentKeyBuffer[key] != 0)
//							{
//								isDown = true;
//								break; // 一つでも押されていれば抜ける
//							}
//						}
//					}
//				}
//
//				_stateArray[i] = isDown; // 最終的な状態決定
//			}
//		};
//
//	UpdateState(gameBindings, currentGameStates, static_cast<int>(ActionID::GameAction::Count)); // ゲーム中
//	UpdateState(uiBindings, currentUIStates, static_cast<int>(ActionID::UI::Count)); // UI操作中
//
//	// Axisに関してはゲーム内のみなのdえUIは行わなくて良い
//	auto Index = [](ActionID::GameAction _key) { return static_cast<int>(_key); };
//
//	// 初期化
//	// axis = Vector2::ZERO;
//
//	// スティック処理
//	float stickX = static_cast<float>(xinputState.ThumbLX);
//	float stickY = static_cast<float>(xinputState.ThumbLY);
//
//	// デッドゾーン処理(少し倒した状態なら無視するようにする)
//	if (std::abs(stickX) < stickRDeadZone) stickX = 0.0f;
//	if (std::abs(stickY) < stickRDeadZone) stickY = 0.0f;
//
//	// sitc変数をVector2にまとめつつ値を-1.0～1.0まで丸める
//	Vector2 stick{ stickX / MAX_XINPUT_VALUE, stickY / MAX_XINPUT_VALUE };
//	axis += stick * stickSensibility;
//	//axis += { stickX,stickY };
//
//	// 移動ベクトル作成
//	if (currentGameStates[Index(ActionID::GameAction::Up)]) axis.y += 1.0f;
//	if (currentGameStates[Index(ActionID::GameAction::Down)]) axis.y -= 1.0f;
//	if (currentGameStates[Index(ActionID::GameAction::Right)]) axis.x += 1.0f;
//	if (currentGameStates[Index(ActionID::GameAction::Left)]) axis.x -= 1.0f;
//
//	// 正規化処理
//	axis.Normalize();
//}
//
