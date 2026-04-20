#pragma once
#include <memory>
#include <map>
#include <functional>
#include "SceneBase.h"

// シーンを作成するためのクラス
class SceneFactory
{
public:
	// 作るシーンを設定する初期化関数
	static void Initialize();
	// シーンを設定するだけで生成できるようにする関数
	static std::unique_ptr<SceneBase> CreateScene(SceneType _type);

private:
	static std::map<SceneType, std::function<std::unique_ptr<SceneBase>()>> creationMap; // key = SceneType, value = 具体シーンのインスタンスを返す関数のmap
};
