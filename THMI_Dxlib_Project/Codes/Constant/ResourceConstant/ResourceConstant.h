#pragma once

// 画像やモデルの種類などの定義

// リソースが必要になるシーン
enum class ResourceUseScene
{
	Common, // 汎用
	Debug, // デバッグシーン(各個人で作成し読み込むのは非効率的と判断しDebugシーンとしてまとめておく)
	Title, // タイトル
	Game, // ゲームシーン
	GameOver, // ゲームオーバー
	GameClaer, // ゲームクリア
};

// 単体画像の種類
enum class SingleTextureKind
{
	None = -1,
	Title, // タイトル
	GameClear, // ゲームクリア
	GameOver, // ゲームオーバー


};

// 3Dモデルの種類
enum class Model3DKind
{
	None = -1,
	Player, // プレイヤー
	Enemy, // 敵
	Ruins, // 遺跡
	WaterSurface, // 水面
	SkySphere, // 天球
};

// ピクセルシェーダーの種類
enum class PSShaderKind
{
	None = -1,
	Toon, // トゥーン調
	Enemy, // 敵専用
	GerstnerWave, // 水面の波
	Depth, // 深度を作る
	ReflectionClip, // 反射制御
	ReflectionColor, // 反射色制御
	MetaBall, // 水滴などのメタボール制御
};

// 頂点シェーダーの種類
enum class VSShaderKind
{
	None = -1,
	Toon, // トゥーン調
	Enemy, // 敵専用
	GerstnerWave, // 水面の波
	Depth, // 深度を作る
	ReflectionClip, // 反射制御
	ReflectionColor, // 反射色制御
	MetaBall, // 水滴などのメタボール制御
};

// サウンドの種類
enum class SoundKind
{
	None = -1,

};
