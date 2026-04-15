#include <Dxlib.h>
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

	int ruinsHandle = ResourceManager::Instance().GetResourceHandle(Model3DKind::Ruins);

	ObjectFactory::CreateDebugObject(VGet(200, 200, 200), ResourceManager::Instance().GetResourceHandle(Model3DKind::Ruins)); 

	SetCameraPositionAndTarget_UpVecY(VGet(100.0f, 200.0f, -10.0f), VGet(200.0f, 200.0f, 200.0f));




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