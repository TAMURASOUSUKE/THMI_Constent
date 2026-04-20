#include <algorithm>
#include "SystemConstant/SystemConstant.h"
#include "../Time/TimeManager.h"
#include "FrameRateManager.h"

FrameRateManager::FrameRateManager(int _currentFPS) : limiter{_currentFPS}
{
	fixedDeltaTime = FIXED_DELTA_TIME; // 固定更新用
	TimeManager::SetProvider(this, this);
}

FrameRateManager::~FrameRateManager()
{
	// 終了時にnullにしておく
	TimeManager::SetProvider(nullptr, nullptr);
}

// フレームの最初に行う処理
void FrameRateManager::Begin()
{
	auto now{ std::chrono::steady_clock::now() }; // 現在の時間取得

	// 2フレーム目以降であればデルタタイム計算を行う
	if (prevFrameStartTime.time_since_epoch().count() != 0)
	{
		std::chrono::duration<float> sec{ now - prevFrameStartTime }; // 一つ前のフレームからの経過時間

		float rawDeltaTime{ sec.count() }; // 実際のデルタタイム

		unscaledDeltaTime = std::min(rawDeltaTime, LIMIT_DELTA_TIME); // デルタタイムを計算(ここではタイムスケールを考慮しない)
		deltaTime = unscaledDeltaTime * timeScale; // タイムスケールと乗算することで実際のデルタタイムを出す
	}

	accumulator += deltaTime; // 積算器にdeltaTimeを加算(固定更新用もタイムスケールの影響を受ける)

	if (accumulator > LIMIT_ACCUMULATOR) accumulator = LIMIT_ACCUMULATOR; // 処理落ちした際にあふれるのを防止する

	CalculateAlpha();

	prevFrameStartTime = now;
	startTime = now;
	currentFPS = counter.GetCurrentFPS();
}

// 残り時間が固定ステップの何割か
void FrameRateManager::CalculateAlpha()
{
	alpha = accumulator / fixedDeltaTime;
}

// タイムスケールの設定
void FrameRateManager::SetTimeScale(const float _scale)
{
	timeScale = std::max(0.0f, _scale);
}

// フレームの最後の処理
void FrameRateManager::End()
{
	limiter.Wait(); // 待機

	counter.Update(startTime); // 計測
}

// accumlator減算処理
void FrameRateManager::ConsumeFixedTime()
{
	accumulator -= FIXED_DELTA_TIME;
	CalculateAlpha();
}

// accumulatorがfixedDeltaTimeを超えているかどうかを返す
bool FrameRateManager::IsFixedUpdateRequired()
{
	return accumulator >= FIXED_DELTA_TIME;
}