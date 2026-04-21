#include <Dxlib.h>
#include "TimeManager.h"
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
	// 描画用処理
	objManager.Draw();

	DebugDrawStrings(); // 文字列表示

}

void TamuraDebugScene::DebugDrawStrings()
{
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

	debugStringPos = 0;

}