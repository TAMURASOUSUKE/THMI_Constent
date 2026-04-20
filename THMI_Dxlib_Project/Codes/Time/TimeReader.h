#pragma once

// 時間情報の読み取り機能を提供するためのインターフェース
class ITimeReader
{
public:
	virtual ~ITimeReader() = default;
	virtual float GetDeltaTime() const = 0; // デルタタイム(タイムスケール適用済み)
	virtual float GetUnscaledDeltaTime() const = 0; // デルタタイム(タイムスケール未適用)
	virtual float GetFixedDeltaTime() const = 0; // 固定更新用のデルタタイム
	virtual float GetCurrentFPS() const = 0; // 現在のFPS
	virtual float GetAlpha() const = 0; // 描画補完アルファ
	virtual float GetTimeScale() const = 0; // タイムスケール
};