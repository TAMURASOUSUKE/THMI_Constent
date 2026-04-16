#pragma once
#include <chrono>
#include "../TimeManagemenet/TimeProvider.h" // Timeクラスに渡すためのプロバイダー
#include "FrameRateCounter.h"
#include "FrameRateLimiter.h"

// FPS,DeltaTime,FixedDeltaTimeの管理を行うクラス
class FrameRateManager : public TimeProvider
{
public:
	FrameRateManager(int _targetFPS); // 引数に設定したいFPSをとるコンストラクタ
	~FrameRateManager(); // デストラクタ

	// コピーコンストラクタの禁止
	FrameRateManager(const FrameRateManager& _other) = delete;
	// コピー代入の禁止
	FrameRateManager operator =(FrameRateManager _other) = delete;

	// フレーム最初の処理
	void Begin();

	// フレーム最後の処理
	void End();

	// accumulatorを減らす処理
	void ConsumeFixedTime();

	// accumulatorがfixedDeltaTimeを超えているかどうかを返す
	bool IsFixedUpdateRequired();

	float GetDeltaTime()      const override { return deltaTime; }
	float GetFixedDeltaTime() const override { return fixedDeltaTime; }
	float GetCurrentFPS()     const override { return currentFPS; }
	float GetAlpha()          const override { return alpha; }

private:
	// 残り時間が固定ステップの何割かを調べる
	void CalculateAlpha();

private:
	time_point<steady_clock> startTime{}; // 待機関数用の開始フレーム
	time_point<steady_clock> prevFrameStartTime{}; // デルタタイム計測用

	FrameRateCounter counter{}; // フレームレートを計測する
	FrameRateLimiter limiter{ 0 }; // 待機用

	float deltaTime{ 0.0f }; // デルタタイム
	float currentFPS{ 0.0f }; // 現在のFPS
	float fixedDeltaTime{ 0.0f }; // 固定更新に使うデルタタイム
	float accumulator{ 0.0f }; // 固定更新用の蓄積時間
	float alpha{ 0.0f }; // 残り時間が固定ステップの何割か

};