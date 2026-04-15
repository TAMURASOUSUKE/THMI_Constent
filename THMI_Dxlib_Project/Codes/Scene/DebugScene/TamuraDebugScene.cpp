#include <Dxlib.h>
#include "TamuraDebugScene.h"
#include "../Object/Bases/ObjectFactory.h"


void TamuraDebugScene::Initialize()
{
	ObjectFactory::BindManager(objManager); // シーンのオブジェクトマネージャーをバインド

	objManager.SortUI(); // UIをソートする

	currentStep = SceneStep::Execute; // 実行処理へ
}

void TamuraDebugScene::Execute()
{

	objManager.Update(); // 更新処理

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
	objManager.Draw();

	// 描画用処理
	DrawString(0, 0, "ここは田村シーンです", GetColor(255, 255, 255), GetColor(255, 255, 255));
}