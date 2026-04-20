#include <Dxlib.h>
#include <string>
#include "ResourceManager.h"

// 指定されたシーンで読み込むファイルをデータとして持つ
void ResourceManager::Load(ResourceUseScene _useScene)
{
	const SingleTextureMap* singleTextures{ dataBase.GetSingleTexture(_useScene) };
	const ModelResourceMap* modelResources{ dataBase.GetModelResource(_useScene) };
	const VSShaderResourceMap* vsShaderResourceMap{ dataBase.GetVSShaderResource(_useScene) };
	const PSShaderResourceMap* psShaderResourceMap{ dataBase.GetPSShaderResource(_useScene) };

	// 読み込み
	Load(vsShaderResourceMap);
	Load(psShaderResourceMap);
	Load(singleTextures);
	Load(modelResources);
}

// 指定されたシーンのリソースを削除する
void ResourceManager::Delete(ResourceUseScene _useScene)
{
	DeleteSingleTexture(_useScene);
	DeleteModel(_useScene);
	DeleteVSShader(_useScene);
	DeletePSShader(_useScene);
	DeleteSound(_useScene);
}

// 指定した画像の種類のハンドルを取得する
int ResourceManager::GetResourceHandle(SingleTextureKind _kind)
{
	if (singleGraphHandles.count(_kind) > 0)
	{
		return singleGraphHandles[_kind];
	}

	return -1;
}

// 指定したモデルの種類のハンドルを取得する
int ResourceManager::GetResourceHandle(Model3DKind _kind)
{
	if (modelHandles.count(_kind) > 0)
	{
		return modelHandles[_kind];
	}

	return -1;
}

// 指定した頂点シェーダーの種類のハンドルを取得する
int ResourceManager::GetResourceHandle(VSShaderKind _kind)
{
	if (vsShaderHandle.count(_kind) > 0)
	{
		return vsShaderHandle[_kind];
	}
	return -1;
}

// 指定したピクセルシェーダーの種類のハンドルを取得する
int ResourceManager::GetResourceHandle(PSShaderKind _kind)
{
	if (psShaderHandle.count(_kind) > 0)
	{
		return psShaderHandle[_kind];
	}
	return -1;
}

// 指定したサウンドの種類のハンドルを取得する
int ResourceManager::GetResourceHandle(SoundKind _kind)
{
	if (soundHandle.count(_kind) > 0)
	{
		return soundHandle[_kind];
	}
	return -1;
}

// 画像の読み込み
void ResourceManager::Load(const SingleTextureMap* _textures)
{
	if (_textures == nullptr)
	{
		return;
	}

	// 重複チェック
	for (auto& fileData : *_textures)
	{
		if (singleGraphHandles.count(fileData.first) > 0)
		{
			continue;
		}

		int handle{ LoadGraph(fileData.second.filePath.c_str()) }; // 画像の読み込み

		if (handle != -1)
		{
			// 読み込みが通ったかを確認してから登録する
			singleGraphHandles[fileData.first] = handle;
		}
	}
}

// モデルの読み込み
void ResourceManager::Load(const ModelResourceMap* _models)
{
	if (_models == nullptr)
	{
		return;
	}

	// 重複チェック
	for (auto& fileData : *_models)
	{
		if (modelHandles.count(fileData.first) > 0)
		{
			continue;
		}

		int handle{ MV1LoadModel(fileData.second.filePath.c_str()) };

		if (handle != -1)
		{
			// 読み込み通ったか確認してから登録する
			modelHandles[fileData.first] = handle;
		}
	}
}

// 頂点シェーダーの読み込み
void ResourceManager::Load(const VSShaderResourceMap* _vsShader)
{
	if (_vsShader == nullptr)
	{
		return;
	}

	// 重複チェック
	for (auto& fileData : *_vsShader)
	{
		if (vsShaderHandle.count(fileData.first) > 0)
		{
			continue;
		}

		int handle{ LoadVertexShader(fileData.second.filePath.c_str()) }; // VSシェーダーの読み込み

		if (handle != -1)
		{
			// 読み込みが通ったかを確認してから登録する
			vsShaderHandle[fileData.first] = handle;
		}
	}
}

// ピクセルシェーダーの読み込み
void ResourceManager::Load(const PSShaderResourceMap* _psShader)
{
	if (_psShader == nullptr)
	{
		return;
	}

	// 重複チェック
	for (auto& fileData : *_psShader)
	{
		if (psShaderHandle.count(fileData.first) > 0)
		{
			continue;
		}

		int handle{ LoadPixelShader(fileData.second.filePath.c_str()) }; // VSシェーダーの読み込み

		if (handle != -1)
		{
			// 読み込みが通ったかを確認してから登録する
			psShaderHandle[fileData.first] = handle;
		}
	}
}

// サウンドの読み込み
void ResourceManager::Load(const SoundResourceMap* _psShader)
{
	if (_psShader == nullptr)
	{
		return;
	}

	// 重複チェック
	for (auto& fileData : *_psShader)
	{
		if (soundHandle.count(fileData.first) > 0)
		{
			continue;
		}

		int handle{ LoadSoundMem(fileData.second.filePath.c_str()) }; // VSシェーダーの読み込み

		if (handle != -1)
		{
			// 読み込みが通ったかを確認してから登録する
			soundHandle[fileData.first] = handle;
		}
	}
}

// 単体画像削除
void ResourceManager::DeleteSingleTexture(ResourceUseScene _useScene)
{
	const SingleTextureMap* singleTextures{ dataBase.GetSingleTexture(_useScene) }; // 削除するデータの取得

	if (singleTextures != nullptr)
	{
		for (auto& fileData : *singleTextures)
		{
			if (singleGraphHandles.count(fileData.first) == 0)
			{
				continue;
			}

			DeleteGraph(singleGraphHandles[fileData.first]);
			singleGraphHandles.erase(fileData.first);
		}
	}
}

// モデル削除
void ResourceManager::DeleteModel(ResourceUseScene _useScene)
{
	const ModelResourceMap* modelResources{ dataBase.GetModelResource(_useScene) };

	if (modelResources != nullptr)
	{
		for (auto& fileData : *modelResources)
		{
			if (modelHandles.count(fileData.first) == 0)
			{
				continue;
			}

			MV1DeleteModel(modelHandles[fileData.first]); // モデルの削除
			modelHandles.erase(fileData.first);
		}
	}
}

// 頂点シェーダー削除
void ResourceManager::DeleteVSShader(ResourceUseScene _useScene)
{
	const VSShaderResourceMap* vsShaderResource{ dataBase.GetVSShaderResource(_useScene) };

	if (vsShaderResource != nullptr)
	{
		for (auto& fileData : *vsShaderResource)
		{
			if (vsShaderHandle.count(fileData.first) == 0)
			{
				continue;
			}

			DeleteShader(vsShaderHandle[fileData.first]); // 頂点シェーダーの削除
			vsShaderHandle.erase(fileData.first);
		}
	}
}

// 頂点シェーダー削除
void ResourceManager::DeletePSShader(ResourceUseScene _useScene)
{
	const PSShaderResourceMap* psShaderResource{ dataBase.GetPSShaderResource(_useScene) };

	if (psShaderResource != nullptr)
	{
		for (auto& fileData : *psShaderResource)
		{
			if (psShaderHandle.count(fileData.first) == 0)
			{
				continue;
			}

			DeleteShader(psShaderHandle[fileData.first]); // 頂点シェーダーの削除
			psShaderHandle.erase(fileData.first);
		}
	}
}

// サウンド削除
void ResourceManager::DeleteSound(ResourceUseScene _useScene)
{
	const SoundResourceMap* soundResource{ dataBase.GetSoundResource(_useScene) };

	if (soundResource != nullptr)
	{
		for (auto& fileData : *soundResource)
		{
			if (soundHandle.count(fileData.first) == 0)
			{
				continue;
			}

			DeleteShader(soundHandle[fileData.first]); // 頂点シェーダーの削除
			soundHandle.erase(fileData.first);
		}
	}
}

void ResourceManager::DeleteAll()
{
	// 該当するシーンを全てリストアップして全削除を行う
	ResourceUseScene deleteScenes[]
	{
		ResourceUseScene::Common,
		ResourceUseScene::Debug,
		ResourceUseScene::Title,
		ResourceUseScene::Game,
		ResourceUseScene::GameClaer,
		ResourceUseScene::GameOver,
	};

	for (auto& scene : deleteScenes)
	{
		// 削除
		Delete(scene);
	}
}
