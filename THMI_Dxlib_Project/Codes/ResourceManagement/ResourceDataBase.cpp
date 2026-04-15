#include <unordered_map>
#include <string>
#include "ResourceDataBase.h"

// そのシーンの単体画像リソースを取得
const SingleTextureMap* ResourceDataBase::GetSingleTexture(ResourceUseScene _useScene)
{
	if (singleTextures.count(_useScene) > 0)
	{
		return &singleTextures[_useScene];
	}

	return nullptr;
}

// そのシーンの3Dモデルリソースを取得
const ModelResourceMap* ResourceDataBase::GetModelResource(ResourceUseScene _useScene)
{
	if (modelResources.count(_useScene) > 0)
	{
		return &modelResources[_useScene];
	}

	return nullptr;
}

// そのシーンの頂点シェーダーリソースを取得
const VSShaderResourceMap* ResourceDataBase::GetVSShaderResource(ResourceUseScene _useScene)
{
	if (vsShaderResources.count(_useScene) > 0)
	{
		return &vsShaderResources[_useScene];
	}
	return nullptr;
}

// そのシーンのピクセルシェーダーリソースを取得
const PSShaderResourceMap* ResourceDataBase::GetPSShaderResource(ResourceUseScene _useScene)
{
	if (psShaderResources.count(_useScene) > 0)
	{
		return &psShaderResources[_useScene];
	}
	return nullptr;
}

// そのシーンのサウンドリソースを取得
const SoundResourceMap* ResourceDataBase::GetSoundResource(ResourceUseScene _useScene)
{
	if (soundResources.count(_useScene) > 0)
	{
		return &soundResources[_useScene];
	}
	return nullptr;
}

// 各シーンに必要なデータベースを作成する
void ResourceDataBase::MakeDataBase()
{
	MakeCommonDataBase();
	MakeDebugDataBase();
	MakeTitleDataBase();
	MakeGameDataBase();
	MakeGameClearDataBase();
	MakeGameOverDataBase();
}

// 汎用データベース
void ResourceDataBase::MakeCommonDataBase()
{
	SingleTextureMap singleTexture
	{

	};

	RegisterSingleTexture(ResourceUseScene::Common, singleTexture);

	PSShaderResourceMap shaders
	{

	};

	RegisterPSShaderResource(ResourceUseScene::Common, shaders);
}

// デバッグシーン用データベース
void ResourceDataBase::MakeDebugDataBase()
{
	SingleTextureMap singleTexture
	{

	};

	RegisterSingleTexture(ResourceUseScene::Debug, singleTexture);

	// モデル指定
	ModelResourceMap modelResource
	{
		{Model3DKind::Player, {"Res/Model/Player/archer04.mv1"}}
	};

	RegisterModelResource(ResourceUseScene::Debug, modelResource);

	PSShaderResourceMap shaders
	{

	};

	RegisterPSShaderResource(ResourceUseScene::Debug, shaders);
}

// タイトルシーン用データベース
void ResourceDataBase::MakeTitleDataBase()
{
	// タイトルで使う画像を指定
	SingleTextureMap singleTexture
	{

	};

	RegisterSingleTexture(ResourceUseScene::Title, singleTexture); // 登録

	// モデル指定
	ModelResourceMap modelResource
	{

	};

	RegisterModelResource(ResourceUseScene::Title, modelResource);
}

// ゲームシーン用データベース
void ResourceDataBase::MakeGameDataBase()
{
	// ゲームで使う画像を指定
	SingleTextureMap singleTexture
	{

	};

	RegisterSingleTexture(ResourceUseScene::Game, singleTexture); // 登録

	// モデル指定
	ModelResourceMap modelResource
	{

	};

	RegisterModelResource(ResourceUseScene::Game, modelResource);
}

// ゲームクリアシーン用データベース
void ResourceDataBase::MakeGameClearDataBase()
{
	// ゲームクリアで使う画像を指定
	SingleTextureMap singleTexture
	{

	};

	RegisterSingleTexture(ResourceUseScene::GameClaer, singleTexture); // 登録

	// モデル指定
	ModelResourceMap modelResource
	{

	};

	RegisterModelResource(ResourceUseScene::GameClaer, modelResource);
}

// ゲームオーバーシーン用データベース
void ResourceDataBase::MakeGameOverDataBase()
{
	// ゲームオーバーで使う画像を指定
	SingleTextureMap singleTexture
	{

	};

	RegisterSingleTexture(ResourceUseScene::GameOver, singleTexture); // 登録

	// モデル指定
	ModelResourceMap modelResource
	{

	};

	RegisterModelResource(ResourceUseScene::GameOver, modelResource);
}

// 単体画像の登録
void ResourceDataBase::RegisterSingleTexture(ResourceUseScene _useScene, SingleTextureMap& _textures)
{
	// マップ内にある画像をシーンと連結させる
	for (auto& texture : _textures)
	{
		singleTextures[_useScene][texture.first] = texture.second;
	}
}

// 3Dモデルの登録
void ResourceDataBase::RegisterModelResource(ResourceUseScene _useScene, ModelResourceMap& _models)
{
	// マップ内にあるモデルとシーンを連結させる
	for (auto& model : _models)
	{
		modelResources[_useScene][model.first] = model.second;
	}
}

// 頂点シェーダーの登録
void ResourceDataBase::RegisterVSShaderResource(ResourceUseScene _useScene, VSShaderResourceMap& _vsShaders)
{
	// マップ内にあるモデルとシーンを連結させる
	for (auto& shader : _vsShaders)
	{
		vsShaderResources[_useScene][shader.first] = shader.second;
	}
}

// ピクセルシェーダーの登録
void ResourceDataBase::RegisterPSShaderResource(ResourceUseScene _useScene, PSShaderResourceMap& _psShaders)
{
	// マップ内にあるモデルとシーンを連結させる
	for (auto& shader : _psShaders)
	{
		psShaderResources[_useScene][shader.first] = shader.second;
	}
}

// サウンドの登録
void ResourceDataBase::RegisterSoundResource(ResourceUseScene _useScene, SoundResourceMap& _sounds)
{
	// マップ内にあるリソースと連結させる
	for (auto& sound : _sounds)
	{
		soundResources[_useScene][sound.first] = sound.second;
	}
}