#include <intrin.h>
#include <Dxlib.h>
#include "SystemConstant/SystemConstant.h"
#include "FrameRateLimiter.h"


FrameRateLimiter::FrameRateLimiter(int _targetFrame)
{
	// 指定したフレームをミリ秒の経過時間に変換する(指定FPSの経過時間)
	targetDuration = std::chrono::microseconds(static_cast<long long>(ONE_SEC_MICRO / _targetFrame));
}

// プロセスメッセージを考慮した時間(ローリングターゲット方式) : 前フレームでオーバーヘッドがあれば次フレームの待機時間を短くし自動補正する
void FrameRateLimiter::Wait()
{
	auto nowTime{ std::chrono::steady_clock::now() }; //　現在の時間

	// 初回は目標時刻の設定
	if (nextFrameTime.time_since_epoch().count() == 0)
	{
		nextFrameTime = nowTime + targetDuration;
	}

	// すでに目標時刻を過ぎていたら(処理落ち処理)
	if (nowTime >= nextFrameTime)
	{
		nextFrameTime = nowTime + targetDuration;
		return;
	}


	auto remainingTime{ nextFrameTime - nowTime }; // 理想の経過時間 - 現在の時間 = 差分

	auto sleepMargin{ std::chrono::milliseconds(1) }; // 1ミリ秒だけ待機時間を短くさせるためのキャッシュ

	if (remainingTime > sleepMargin)
	{
		auto sleepTime{ std::chrono::duration_cast<std::chrono::milliseconds>(remainingTime - sleepMargin) }; //実際の待機時間

		Sleep(static_cast<DWORD>(sleepTime.count())); // 待機する
	}

	// 目標時刻になるまで空回しさせる
	while (std::chrono::steady_clock::now() < nextFrameTime)
	{
		_mm_pause(); // ビジーループ対策にCPU最適化処理を入れる
	}

	nextFrameTime += targetDuration; // 一定間隔で進める

}