#pragma once
#include "ResourceConstant/ResourceData.h"
#include "ResourceConstant/ResourceConstant.h"


//　リソース管理用のデータベース
class ResourceDataBase
{
public:

	ResourceDataBase()
	{
		MakeDataBase(); // コンストラクタで一気に作成する
	}

	const SingleTextureMap* GetSingleTexture(ResourceUseScene _useScene); // 該当シーンを引数に画像単体を取得
	const ModelResourceMap* GetModelResource(ResourceUseScene _useScene); // 該当シーンを引数にモデルを取得する取得
	const VSShaderResourceMap* GetVSShaderResource(ResourceUseScene _useScene); // 該当シーンを引数に頂点シェーダを取得
	const PSShaderResourceMap* GetPSShaderResource(ResourceUseScene _useScene); // 該当シーンを引数にピクセルシェーダを取得
	const SoundResourceMap* GetSoundResource(ResourceUseScene _useScene); // 該当シーンを引数にBGMやSEを取得

private:
	void MakeDataBase(); // DataBase作成を取りまとめる


	// シーンごとにDataBaseを作る
	void MakeCommonDataBase(); // 汎用DataBase
	void MakeDebugDataBase(); // デバッグのDataBase
	void MakeTitleDataBase(); // タイトルDataBase
	void MakeGameDataBase(); // ゲーム用のDataBase
	void MakeGameOverDataBase(); // ゲームオーバー用のDataBase
	void MakeGameClearDataBase(); // ゲームクリア用のDataBase

	// リソースごとのデータ作成関数
	void RegisterSingleTexture(ResourceUseScene _useScene, SingleTextureMap& _textures); // 単体画像のデータ作成 
	void RegisterModelResource(ResourceUseScene _useScene, ModelResourceMap& _models); // モデルリソースのデータ作成
	void RegisterPSShaderResource(ResourceUseScene _useScene, PSShaderResourceMap& _psShaders); // PSシェーダーリソースのデータ作成
	void RegisterVSShaderResource(ResourceUseScene _useScene, VSShaderResourceMap& _vsShaders); // VSシェーダーリソースのデータ作成
	void RegisterSoundResource(ResourceUseScene _useScene, SoundResourceMap& _sounds); // サウンドリソースのデータ作成

private:
	// ファイル情報保存用変数
	UseSingleTextureMap singleTextures{}; // 単体画像
	UseModelResourceMap modelResources{}; // モデル
	UsePSShaderResourceMap psShaderResources{}; // PSシェーダー
	UseVSShaderResourceMap vsShaderResources{}; // VSシェーダー
	UseSoundResourceMap soundResources{}; // サウンド

};