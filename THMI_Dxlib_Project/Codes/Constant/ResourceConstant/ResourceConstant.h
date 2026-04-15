#pragma once

// 画像やモデルの種類などの定義

// リソースが必要になるシーン
enum class ResourceUseScene
{
	Common, // 汎用
	Debug, // デバッグシーン
	TamuraScene, // 田村用
	Mizushima, // 水島用
	Hashino, // 橋野用
	Itou, // 伊藤用
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

enum class Model3DKind
{
	None = -1,
	Gun, // 銃
	Ground, // 背景
	Obstacles, // 壁などのステージ
	Target, // 的
	Player, // Player
};

enum class PSShaderKind
{
	None = -1,
	Crack, // ひび割れ
};

enum class VSShaderKind
{
	None = -1,

};

enum class FontKind
{
	None = -1,
	Meiryo // メイリオ
};

