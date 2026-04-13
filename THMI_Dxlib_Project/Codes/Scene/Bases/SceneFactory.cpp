#include "SceneFactory.h"

// 具体シーンのインクルード
#include "../DebugScene/ChooseDebugScene.h"
#include "../DebugScene/HashinoDebugScene.h"
#include "../DebugScene/ItouDebugScene.h"
#include "../DebugScene/MizushimaDebugScene.h"
#include "../DebugScene/TamuraDebugScene.h"

std::map<SceneType, std::function<std::unique_ptr<SceneBase>()>> SceneFactory::creationMap; // メンバ変数の実体

void SceneFactory::Initialize()
{
	creationMap[SceneType::ChooseDebug] = []() { return std::make_unique<ChooseDebugScene>(); }; // デバッグシーン選択用シーンを作成する
	creationMap[SceneType::ChooseDebug] = []() { return std::make_unique<HashinoDebugScene>(); }; // 橋野デバッグシーンを作成する
	creationMap[SceneType::ChooseDebug] = []() { return std::make_unique<ItouDebugScene>(); }; // 伊藤デバッグシーンを作成する
	creationMap[SceneType::ChooseDebug] = []() { return std::make_unique<MizushimaDebugScene>(); }; // 水島デバッグシーンを作成する
	creationMap[SceneType::ChooseDebug] = []() { return std::make_unique<TamuraDebugScene>(); }; // 田村デバッグシーンを作成する
}

std::unique_ptr<SceneBase> SceneFactory::CreateScene(SceneType _type)
{
	auto it{ creationMap.find(_type) }; // 引数に入れたtypeがkeyとして存在するかを探す
	if (it != creationMap.end())
	{
		return it->second(); // Initializeで設定した関数の結果を返す
	}
	return nullptr;
}