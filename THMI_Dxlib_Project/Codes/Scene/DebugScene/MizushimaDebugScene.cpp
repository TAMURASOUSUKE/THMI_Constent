#include <Dxlib.h>
#include "../Object/Bases/ObjectFactory.h"
#include "MizushimaDebugScene.h"


void MizushimaDebugScene::Initialize()
{
	ObjectFactory::BindManager(objManager); // シーンのオブジェクトマネージャーをバインド

	objManager.SortUI(); // UIをソートする

	currentStep = SceneStep::Execute; // 実行処理へ
}

void MizushimaDebugScene::Execute()
{
	objManager.Update(); // 更新処理

	// Enterを押すことでシーンを抜ける処理へ
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		currentStep = SceneStep::Terminate; // シーンを抜ける際の処理へ
	}
}

void MizushimaDebugScene::FixedExecute()
{
	// 固定更新用処理
	objManager.FixedUpdate();
}

SceneType MizushimaDebugScene::Terminate()
{
	// シーンを抜ける際の処理
	return SceneType::ChooseDebug; // 選択シーンに戻すようにしていますがプロジェクトの進行に合わせて変える可能性があります。
}

void MizushimaDebugScene::Draw()
{
	objManager.Draw();


	// 描画用処理
	DrawString(0, 0, "ここは水島シーンです", GetColor(255, 255, 255), GetColor(255, 255, 255));
}