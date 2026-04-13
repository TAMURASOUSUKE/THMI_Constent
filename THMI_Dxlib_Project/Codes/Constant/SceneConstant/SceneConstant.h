#pragma once

// シーンに関する汎用構造体を定義する

// シーンの種類
enum class SceneType
{
	None = -1, // 未定義
	ChooseDebug, // どのデバッグシーンに行くのかを選択するシーン
	Tamura,  // 田村用デバッグシーン
	Mizushima, // 水島用デバッグシーン
	Hashino, // 橋野用デバッグシーン
	Itou, // 伊藤用デバッグシーン
	Title, // タイトルシーン
	Game, // ゲームシーン
	GameOver, // ゲームオーバーシーン
	GameClear, // ゲームクリアシーン
};

// シーン中のフェーズ
enum class SceneStep
{
	None = -1, // 未定義
	Initialize, // 切り替わった最初のフレームの処理
	Execute, // シーン実行中の処理
	Terminate, // シーンを抜ける時の処理
};