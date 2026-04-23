#include <Dxlib.h>
#include "../ResourceManagement/ResourceManager.h"
#include "../Object/Bases/ObjectFactory.h"
#include "MizushimaDebugScene.h"

#include "MDMath.h"


MizushimaDebugScene::~MizushimaDebugScene()
{
	ResourceManager::Instance().Delete(ResourceUseScene::Debug); // リソースの削除
}

void MizushimaDebugScene::Initialize()
{
	ResourceManager::Instance().Load(ResourceUseScene::Debug); // リソースのロード

	ObjectFactory::BindManager(objManager); // シーンのオブジェクトマネージャーをバインド

	objManager.SortUI(); // UIをソートする

	// モデルハンドル
	handle = ResourceManager::Instance().GetResourceHandle(Model3DKind::Player);

	SetCameraPositionAndTarget_UpVecY(Vector3{ MV1GetPosition(handle) } - Vector3{ 0,0,100.0f }, MV1GetPosition(handle));

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


	trs.Rotate(Quaternion::AngleAxis(DX_PI_F / 3.0f, Vector3::UP));

	if (timer++ >= 120)
	{
		rot = trs.GetRotate();

		

		norm = sqrtf(Quaternion::Dot(trs.GetRotate(), trs.GetRotate()));

		timer = 0;
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

	MV1SetMatrix(handle, trs.GetWorldMatrix());

	MV1DrawModel(handle);

	DrawString(200, 0, std::to_string(norm).c_str(), GetColor(255, 255, 255), GetColor(255, 255, 255));

	DrawString(200, 20, std::to_string(trs.GetRotate().x).c_str(), GetColor(255, 255, 255), GetColor(255, 255, 255));
	DrawString(200, 40, std::to_string(trs.GetRotate().y).c_str(), GetColor(255, 255, 255), GetColor(255, 255, 255));
	DrawString(200, 60, std::to_string(trs.GetRotate().z).c_str(), GetColor(255, 255, 255), GetColor(255, 255, 255));
	DrawString(200, 80, std::to_string(trs.GetRotate().w).c_str(), GetColor(255, 255, 255), GetColor(255, 255, 255));

	DrawString(200, 120, std::to_string(rot.x).c_str(), GetColor(255, 255, 255), GetColor(255, 255, 255));
	DrawString(200, 140, std::to_string(rot.y).c_str(), GetColor(255, 255, 255), GetColor(255, 255, 255));
	DrawString(200, 160, std::to_string(rot.z).c_str(), GetColor(255, 255, 255), GetColor(255, 255, 255));
	DrawString(200, 180, std::to_string(rot.w).c_str(), GetColor(255, 255, 255), GetColor(255, 255, 255));
}