#include <Dxlib.h>
#include "HashinoDebugScene.h"

void HashinoDebugScene::Draw()
{
	// 描画用処理
}

void HashinoDebugScene::Initialize()
{
	currentStep = SceneStep::Execute; // 実行処理へ
}

void HashinoDebugScene::Execute()
{


	// Enterを押すことでシーンを抜ける処理へ
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		currentStep = SceneStep::Terminate; // シーンを抜ける際の処理へ
	}
}

void HashinoDebugScene::FixedExecute()
{
	// 固定更新用処理
}

SceneType HashinoDebugScene::Terminate()
{
	// シーンを抜ける際の処理
	return SceneType::ChooseDebug; // 選択シーンに戻すようにしていますがプロジェクトの進行に合わせて変える可能性があります。
}