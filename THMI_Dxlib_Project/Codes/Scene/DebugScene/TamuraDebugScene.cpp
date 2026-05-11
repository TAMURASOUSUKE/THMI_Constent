#include <Dxlib.h>
#include "TimeManager.h"
#include "InputManager.h"
#include "../ResourceManagement/ResourceManager.h"
#include "../Object/Bases/ObjectFactory.h"
#include "TamuraDebugScene.h"


TamuraDebugScene::~TamuraDebugScene()
{
	ResourceManager::Instance().Delete(ResourceUseScene::Debug); // リソースの削除
}

void TamuraDebugScene::Initialize()
{
	ResourceManager::Instance().Load(ResourceUseScene::Debug); // リソースのロード

	ObjectFactory::BindManager(objManager); // シーンのオブジェクトマネージャーをバインド

	ObjectFactory::CreateDebugObject(VGet(200, 200, 200), ResourceManager::Instance().GetResourceHandle(Model3DKind::Enemy)); 

	SetCameraPositionAndTarget_UpVecY(VGet(100.0f, 200.0f, -10.0f), VGet(200.0f, 200.0f, 200.0f));




	objManager.SortUI(); // UIをソートする

	currentStep = SceneStep::Execute; // 実行処理へ
}

void TamuraDebugScene::Execute()
{
	InputManager::Instance().Update(); // 入力更新

	objManager.Update(); // 更新処理

	if (CheckHitKey(KEY_INPUT_F)) currentDebugMode = DebugString::Frame; // フレームモード
	else if (CheckHitKey(KEY_INPUT_I)) currentDebugMode = DebugString::Input; // 入力モード
	else if (CheckHitKey(KEY_INPUT_N)) currentDebugMode = DebugString::None; // 全解除

	// Enterを押すことでシーンを抜ける処理へ
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		currentStep = SceneStep::Terminate; // シーンを抜ける際の処理へ
	}
}

void TamuraDebugScene::FixedExecute()
{
	// 固定更新用処理
	objManager.FixedUpdate();
}

SceneType TamuraDebugScene::Terminate()
{
	// シーンを抜ける際の処理
	return SceneType::ChooseDebug; // 選択シーンに戻すようにしていますがプロジェクトの進行に合わせて変える可能性があります。
}

void TamuraDebugScene::Draw()
{
	// 描画用処理
	objManager.Draw();

	// デバッグモード状態によって表示する文字列を切り替える
	switch (currentDebugMode)
	{
	case DebugString::None:
		break;
	case DebugString::Frame:
		DebugFrameStrings(); // フレーム関連の文字列表示
		break;
	case DebugString::Input:
		DebugInputStrings(); // 入力関連の文字列表示
		break;
	default:
		break;
	}

}

// フレーム関連のデバッグ用文字列
void TamuraDebugScene::DebugFrameStrings()
{
	debugStringPos = 0;

	// 描画用処理
	DrawString(0, debugStringPos, "ここは田村シーンです", debugWhite, debugRed);

	debugStringPos += debugStringHeight; // 行間

	DrawFormatString(0, debugStringPos, debugWhite, "現在のFPS : %.1f", TimeManager::GetCurrentFPS());

	debugStringPos += debugStringHeight; // 行間

	DrawFormatString(0, debugStringPos, debugWhite, "現在のDeltaTime : %.4f", TimeManager::DeltaTime());

	debugStringPos += debugStringHeight; // 行間

	DrawFormatString(0, debugStringPos, debugWhite, "現在のUnscaledDeltaTime : %.4f", TimeManager::UnscaledDeltaTime());

	debugStringPos += debugStringHeight; // 行間

	DrawFormatString(0, debugStringPos, debugWhite, "現在のFixedDeltaTime : %.4f", TimeManager::FixedDeltaTime());

	debugStringPos += debugStringHeight; // 行間

	DrawFormatString(0, debugStringPos, debugWhite, "現在のAlpha : %.1f", TimeManager::Alpha());

	debugStringPos += debugStringHeight; // 行間

	DrawFormatString(0, debugStringPos, debugWhite, "現在のTimeScale : %f", TimeManager::GetTimeScale());

}

// 入力関連のデバッグ用文字列
void TamuraDebugScene::DebugInputStrings()
{
	debugStringPos = 0;

	// 現在の入力状態を表示
	std::string currentInputState{ "" };

	switch (InputManager::Instance().GetInputMode())
	{
	case InputMode::Game:
		currentInputState = "GameMode";
		break;
	case InputMode::Menu:
		currentInputState = "MenuMode";
		break;
	case InputMode::Config:
		currentInputState = "CofigMode";
		break;
	case InputMode::None:
		currentInputState = "ModeNone";
		break;
	}

	// 入力状態の表示
	DrawFormatString(0, debugStringPos, debugWhite, "現在の入力モード : %s", currentInputState.c_str());

	debugStringPos += debugStringHeight; // 行間

	// 軸入力の確認
	Vector2 axis{ InputManager::Instance().GetAxis() }; // 軸入力の取得
	DrawFormatString(0, debugStringPos, debugWhite, "Axis : (%.2f, %.2f)", axis.x, axis.y);

	debugStringPos += debugStringHeight; // 行間

	// トリガーを押す深さ
	DrawFormatString(0, debugStringPos, debugWhite, "トリガーデッドゾーン : %d", InputManager::Instance().GetTriggerDeadZone());

	debugStringPos += debugStringHeight; // 行間

	// ボタンの確認
	// 押されていれば文字が赤くなるようにする
	auto DrawButtonState = [&](const char* name, auto key)
		{
			unsigned int color = InputManager::Instance().GetButtonStay(key) ? debugRed : debugWhite; // 押し続けていれば赤

			const char* status = ""; // ステータスを文字列にする
			if (InputManager::Instance().GetButtonDown(key)) status = "DWN";
			if (InputManager::Instance().GetButtonUp(key)) status = "UP";

			DrawFormatString(0, debugStringPos, color, "[%s] %s %s", status, name, InputManager::Instance().GetButtonStay(key) ? "ON" : "off");

			debugStringPos += debugStringHeight;;

		};

	// 主要なキーを表示
	DrawButtonState("Game : Attack", ActionID::GameAction::Attack);
	DrawButtonState("Game : Avoid", ActionID::GameAction::Avoid);
	DrawButtonState("Game : Up", ActionID::GameAction::Up);
	DrawButtonState("Game : Down", ActionID::GameAction::Down);
	DrawButtonState("Game : Left", ActionID::GameAction::Left);
	DrawButtonState("Game : Right", ActionID::GameAction::Right);
	DrawButtonState("UI : Up", ActionID::UI::Up);
	DrawButtonState("UI : Down", ActionID::UI::Down);
	DrawButtonState("UI : Right", ActionID::UI::Right);
	DrawButtonState("UI : Left", ActionID::UI::Left);
	DrawButtonState("UI : Decide", ActionID::UI::Decide);
	DrawButtonState("UI : Cancel", ActionID::UI::Cancel);
	DrawButtonState("UI : Pause", ActionID::UI::Pause);

	// JSON保存のテスト用
	if (InputManager::Instance().GetButtonDown(ActionID::GameAction::Avoid))
	{
		DrawString(200, 100, "Save Config Triggered!", debugRed);
		InputManager::Instance().SaveConfig();
	}

	// キーコンフィグを変更できるか確認する
	static bool isRebindingJumpKey{ false }; // 新しくキーを設定するかどうかを判定するフラグ(簡易的なテストなのでstatic)
	static bool isRebindingDashPad{ false }; // 新しくダッシュボタンをパッドで設定するかどうかを判定する

	if (isRebindingJumpKey)
	{
		// 変更モード中を表示
		DrawString(0, debugStringPos, ">> Press Any Key for [Attack] <<", debugRed);

		int newKey{ InputManager::Instance().GetAnyPressedKey() }; // 入力されたキーを判別し保存する

		// キーが押されているかつ変更モードを起動するキー以外が押されたら登録する
		if (newKey != -1 && newKey != KEY_INPUT_C)
		{
			// 入力されたキーに変更
			InputManager::Instance().SetBindingKey(ActionID::GameAction::Attack, newKey);

			// 保存する
			InputManager::Instance().SaveConfig();

			// 変更モード終了
			isRebindingJumpKey = false;
		}
	}
	else
	{
		// 通常時の文字列表示
		DrawString(0, debugStringPos, "[C] key : Change 'Attack' Binding", debugWhite);

		// Cキーで変更モードへ
		if (CheckHitKey(KEY_INPUT_C))
		{
			isRebindingJumpKey = true;
		}
	}

	debugStringPos += debugStringHeight;

	if (isRebindingDashPad)
	{
		// ボタン変更状態
		DrawString(0, debugStringPos, ">> Press Any Pad Button for [Attack] <<", debugRed);

		int newButton{ InputManager::Instance().GetAnyPressedButton()}; // 入力されたボタンを受け取る

		if (newButton != 0 && newButton != PadCode::TRIGGER_L) // 新しいボタンが押されているかつ左トリガー以外の場合
		{
			InputManager::Instance().SetBindingPad(ActionID::GameAction::Attack, newButton); // 新しいボタンを設定

			InputManager::Instance().SaveConfig(); // 新しいボタンをセーブ

			isRebindingDashPad = false; // キーコン更新を終了
		}
	}
	else
	{
		// 通常状態
		DrawString(0, debugStringPos, "[TriggerL] Button : Change 'Attack' Binding", debugWhite);

		if ((InputManager::Instance().GetAnyPressedButton() & PadCode::TRIGGER_L) != 0) // テスト用にトリガーLボタンで変更できるようにする
		{
			isRebindingDashPad = true;
		}
	}

	debugStringPos += debugStringHeight;

	// モード変更
	if (CheckHitKey(KEY_INPUT_M))
	{
		InputManager::Instance().SetInputMode(InputMode::Menu);
	}
	else if (CheckHitKey(KEY_INPUT_G))
	{
		InputManager::Instance().SetInputMode(InputMode::Game);
	}

	// カメラ用Axisデバッグ
	Vector2 camAxis{ InputManager::Instance().GetCameraAxis() }; // Axisを正しく取得できるかをテストする変数
	DrawString(0, debugStringPos, "---- Camera Input ----", debugWhite);
	debugStringPos += debugStringHeight;
	DrawFormatString(0, debugStringPos, debugWhite, "Camera Axis: (%.3f, %.3f)", camAxis.x, camAxis.y);

	// マウス座標も表示しておく
	debugStringPos += debugStringHeight;
	int mx;
	int my;
	GetMousePoint(&mx, &my);
	DrawFormatString(0, debugStringPos, debugWhite, "Raw MousePosition: (%d, %d)", mx, my);

	debugStringPos += debugStringHeight;

	// 各種設定値表示
	DrawFormatString(0, debugStringPos, debugWhite, "TriggerDeadZone : %d", InputManager::Instance().GetTriggerDeadZone());

	debugStringPos += debugStringHeight;

	DrawFormatString(0, debugStringPos, debugWhite, "RightStickDeadZone : %d", InputManager::Instance().GetStickDeadZone());

	debugStringPos += debugStringHeight;

	DrawFormatString(0, debugStringPos, debugWhite, "RightStickSensibility: %.3f", InputManager::Instance().GetStickSensibility());

	debugStringPos += debugStringHeight;

	DrawFormatString(0, debugStringPos, debugWhite, "RightStickSensibility: %.3f", InputManager::Instance().GetMouseSensibility());


}