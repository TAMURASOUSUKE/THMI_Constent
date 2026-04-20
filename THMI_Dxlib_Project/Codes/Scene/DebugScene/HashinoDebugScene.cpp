#include <Dxlib.h>
#include "../ResourceManagement/ResourceManager.h"
#include "../Object/Bases/ObjectFactory.h"
#include "HashinoDebugScene.h"

HashinoDebugScene::~HashinoDebugScene()
{
	ResourceManager::Instance().Delete(ResourceUseScene::Debug); // リソースの削除
}

void HashinoDebugScene::Initialize()
{
	ResourceManager::Instance().Load(ResourceUseScene::Debug); // リソースのロード

	ObjectFactory::BindManager(objManager); // シーンのオブジェクトマネージャーをバインド

	objManager.SortUI(); // UIをソートする

	currentStep = SceneStep::Execute; // 実行処理へ
}

void HashinoDebugScene::Execute()
{
	objManager.Update(); // 更新処理

	// Enterを押すことでシーンを抜ける処理へ
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		currentStep = SceneStep::Terminate; // シーンを抜ける際の処理へ
	}
}

void HashinoDebugScene::FixedExecute()
{
	// 固定更新用処理
	objManager.FixedUpdate();
}

SceneType HashinoDebugScene::Terminate()
{
	// シーンを抜ける際の処理
	return SceneType::ChooseDebug; // 選択シーンに戻すようにしていますがプロジェクトの進行に合わせて変える可能性があります。
}

void HashinoDebugScene::Draw()
{
	objManager.Draw();

	// 描画用処理
	DrawString(0, 0, "ここは橋野シーンです", GetColor(255, 255, 255), GetColor(255, 255, 255));
}