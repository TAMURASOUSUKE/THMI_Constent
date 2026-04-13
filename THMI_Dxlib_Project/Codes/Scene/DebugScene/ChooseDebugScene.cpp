#include <Dxlib.h>
#include "ChooseDebugScene.h"

void ChooseDebugScene::Draw()
{
	// 画面に表示する文字列
	DrawString(20, 40, "ここはデバッグシーンを選択するシーンです。押されたキーによってシーンが切り替わります", GetColor(255, 255, 255));
	DrawString(20, 60, "F1 -> 田村用デバッグシーン", GetColor(255, 255, 255));
	DrawString(20, 80, "F2 -> 水島用デバッグシーン", GetColor(255, 255, 255));
	DrawString(20, 100, "F3 -> 橋野用デバッグシーン", GetColor(255, 255, 255));
	DrawString(20, 120, "F4 -> 伊藤用デバッグシーン", GetColor(255, 255, 255));
	DrawString(20, 140, "各デバッグシーンではEnterを押すとこのシーンヘ戻ってくるようにしています", GetColor(255, 255, 255));
}

void ChooseDebugScene::Initialize()
{
	currentStep = SceneStep::Execute; // 実行処理へ
}

void ChooseDebugScene::Execute()
{
	currentStep = SceneStep::Terminate; // シーンを抜ける際の処理へ
}

void ChooseDebugScene::FixedExecute()
{
	// 特に物理更新等はないので空
}

SceneType ChooseDebugScene::Terminate()
{
	// 押されたキーによって次のシーンを決定
	if (CheckHitKey(KEY_INPUT_F1)) return SceneType::Tamura;
	if (CheckHitKey(KEY_INPUT_F2)) return SceneType::Mizushima;
	if (CheckHitKey(KEY_INPUT_F3)) return SceneType::Hashino;
	if (CheckHitKey(KEY_INPUT_F4)) return SceneType::Itou;
}