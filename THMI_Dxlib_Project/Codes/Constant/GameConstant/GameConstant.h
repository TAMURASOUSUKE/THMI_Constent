#pragma once

// ゲーム内に関係する定数や汎用構造体を定義する

// オブジェクトを描画する際に必要なLayer
enum class RenderLayer
{
	None = -1, // 未定義
	World, // 3D空間に存在するオブジェクトに付与されるレイヤー
	UI, // 2Dの画像やその他として存在するオブジェクト
};