#pragma once
#include <chrono>

// FPSの計測を行うクラス
class FrameRateCounter
{
public:
	FrameRateCounter() = default;
	~FrameRateCounter() = default;

	// 現在のFPSを取得する
	const float GetCurrentFPS() const { return currentFPS; }

	// コピーコンストラクタの禁止
	FrameRateCounter(const FrameRateCounter& _other) = delete;
	// コピー代入の禁止
	FrameRateCounter operator =(FrameRateCounter _other) = delete;

	/// <summary>
	/// フレームレートの計測を行う
	/// </summary>
	/// <param name="currentTime">現在の時間点</param>
	void Update(const std::chrono::time_point<std::chrono::steady_clock>& _currentTime);

private:
	std::chrono::time_point<std::chrono::steady_clock> startTime{}; // FPSの測定開始時刻
	int frameCounter{ 0 }; // フレームを計測する計測器
	float currentFPS{ 0.0f }; // 現在のFPS値を記録する
};