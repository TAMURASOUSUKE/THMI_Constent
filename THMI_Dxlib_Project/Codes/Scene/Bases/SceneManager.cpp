#include "SceneFactory.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{
	SceneFactory::Initialize(); // 使用するシーンの登録
}

void SceneManager::SetFirstScene(SceneType _type)
{
	currentScene = SceneFactory::CreateScene(_type); // 設定したタイプのシーンを生成する
}

void SceneManager::Update()
{
	if (currentScene == nullptr) return;

	// 通常時の更新
	SceneType type{ currentScene->Update() }; // 各処理を実行しつつそのフレームのtypeを取得

	// typeに入ったシーンが現在のシーンと違っていたらそのシーンへ切り替える
	if (type != currentScene->GetType())
	{
		currentScene = SceneFactory::CreateScene(type); // 新しいシーンを生成する
	}
}

void SceneManager::FixedUpdate()
{
	// 固定時間更新
	currentScene->FixedUpdate();
}

void SceneManager::Draw()
{
	// 中身が入っているかを確認
	if (currentScene == nullptr) return;

	currentScene->Draw(); // 描画
}