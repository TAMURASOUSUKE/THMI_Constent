#pragma once
#include <chrono>

using namespace std::chrono; // 変数省略

// 現在の時間を受け取り指定されたFPSになるように調整するクラス
class FrameRateLimiter
{
public:
	FrameRateLimiter(int _targetFPS); // 指定FPSを引数に取るコンストラクタ
	~FrameRateLimiter() = default; // デフォルトデストラクタ

	// コピーコンストラクタの禁止
	FrameRateLimiter(const FrameRateLimiter& _other) = delete;
	// コピー代入の禁止
	FrameRateLimiter operator =(FrameRateLimiter _other) = delete;

	/// <summary>
	/// 理想の時間とかかった時間を求めその差分だけ待機する
	/// </summary>
	/// <param name="_startTime">開始時刻</param>
	void Wait(time_point<steady_clock> _startTime);

private:
	microseconds targetDuration{}; // 指定された時間をFPSに変換する

};