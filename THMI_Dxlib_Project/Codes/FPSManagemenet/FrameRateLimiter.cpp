#include <intrin.h>
#include <Dxlib.h>
#include "SystemConstant/SystemConstant.h"
#include "FrameRateLimiter.h"

FrameRateLimiter::FrameRateLimiter(int _targetFrame)
{
	// 指定したフレームをミリ秒の経過時間に変換する(指定FPSの経過時間)
	targetDuration = microseconds(static_cast<long long>(ONE_SEC_MICRO / _targetFrame));
}

void FrameRateLimiter::Wait(time_point<steady_clock> _startTime)
{
	auto targetTime{ targetDuration + _startTime }; // 指定FPSの経過時間 + 開始時間 = 目標経過時間

	auto nowTime{ steady_clock::now() }; //　現在の時間

	auto remainingTime{ targetTime - nowTime }; // 理想の経過時間 - 現在の時間 = 差分

	if (remainingTime.count() <= 0) // 目標時間よりも経過時間の方が多かった場合
	{
		// 処理落ち時の処理
		return;
	}

	auto sleepMargin{ milliseconds(1) }; // 1ミリ秒だけ待機時間を短くさせるためのキャッシュ

	if (remainingTime > sleepMargin)
	{
		auto sleepTime{ duration_cast<milliseconds>(remainingTime - sleepMargin) }; //実際の待機時間

		Sleep(static_cast<DWORD>(sleepTime.count())); // 待機する
	}

	// 目標時刻になるまで空回しさせる
	while (steady_clock::now() < targetTime)
	{
		_mm_pause(); // ビジーループ対策にCPU最適化処理を入れる
	}

}