#include "SceneFactory.h"

// 具体シーンのインクルード

std::map<SceneType, std::function<std::unique_ptr<SceneBase>()>> SceneFactory::creationMap; // メンバ変数の実体

void SceneFactory::Initialize()
{

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