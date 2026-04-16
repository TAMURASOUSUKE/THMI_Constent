#pragma once
#include "TimeReader.h"
#include "TimeController.h"

// 時間に関する機能を提供する
class Time
{
public:
	Time() = delete; // インスタンスを作ることを禁止する

	static void SetProvider(const ITimeReader* _readerProvider, ITimeController* _controllerProvider); // プロバイダーの接続を行う
	static void SetTimeScale(const float _scale); // タイムスケールの設定を行う

	static float DeltaTime(); // デルタタイムの取得
	static float UnscaledDeltaTime(); // タイムスケールを考慮しないデルタタイムの取得
	static float FixedDeltaTime(); // 固定更新用のデルタタイム
	static float Alpha(); // 描画補完用アルファの取得
	static float GetCurrentFPS(); // 現在のFPS
	static float GetTimeScale(); // タイムスケールの取得

private:
	static const ITimeReader* readerProvider; // 読み取り接続用インターフェース
	static ITimeController* controllerProvider; // 設定接続用インターフェース
};
