#pragma once
#include <memory>
#include "SceneConstant/SceneConstant.h"
#include "SceneBase.h"

// シーンを管理するクラス
class SceneManager
{
public:
	// コンストラクタ
	SceneManager();
	~SceneManager() = default;

	// 最初のシーンを決定する関数
	void SetFirstScene(SceneType _type);

	// 更新関数
	void Update();
	// 固定時間更新関数
	void FixedUpdate();
	// 描画関数
	void Draw();

private:
	std::unique_ptr<SceneBase> currentScene; // 現在のシーンのポインタ

};
