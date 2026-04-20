#pragma once
#include "ObjectBase.h"
#include "DxLib.h"

// UIなど2D座標を用い画像として存在するオブジェクトの規定となるクラス
class UIObjectBase : public ObjectBase
{
public:
	UIObjectBase() = default;
	~UIObjectBase() = default;

	// 座標を初期化
	UIObjectBase(float _x, float _y) : x{ _x }, y{ _y }, ObjectBase(RenderLayer::UI) {}

	// 色の設定
	void SetColor(unsigned int _c) { color = _c; }

	// 透明度の設定
	void SetAlpha(float _a) { alpha = _a; }

	// 透明かどうかのフラグ
	bool GetIsVisible() { return isVisible; }

	// 表示フラグ
	void SetVisble(bool _visible) { isVisible = _visible; }

	// 描画優先度の取得
	int GetPriority() { return priority; }

	// 描画優先度の設定
	void SetPriority(int _p) { priority = _p; }

protected:

	// 色の取得
	unsigned int GetDrawColor() const { return color; }

	// Dxlibの透明度を取得
	int GetDxLibAlpha() const { return static_cast<int>(alpha * 255.0f); }

protected:
	float x{ 0.0f }; // x座標
	float y{ 0.0f }; // yz座標
	unsigned int color{ GetColor(255, 255, 255) }; // 色(デフォルトは白)
	int priority{ 0 }; // 描画優先度
	float alpha{ 0.0f }; // 透明度
	bool isVisible{ true }; // 描画フラグ
};