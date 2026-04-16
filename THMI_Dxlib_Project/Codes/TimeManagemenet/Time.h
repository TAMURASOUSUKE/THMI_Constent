#pragma once
#include "TimeProvider.h"

// 時間に関する機能を提供する
class Time
{
public:

	Time() = delete; // インスタンスを作ることを禁止する

	static void SetProvider(const TimeProvider* _provider); // プロバイダーの接続を行う

	static float DeltaTime(); // デルタタイムの取得
	static float FixedDeltaTime(); // 固定更新用のデルタタイム
	static float GetCurrentFPS(); // 現在のFPS
	static float GetAlpha(); // 描画補完用アルファの取得

private:
	static const TimeProvider* provider; // 接続用インターフェース
};
