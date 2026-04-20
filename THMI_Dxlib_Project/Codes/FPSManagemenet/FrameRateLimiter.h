#pragma once
#include <chrono>

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

	// 理想の時間とかかった時間を求めその差分だけ待機する
	void Wait();

private:
	std::chrono::microseconds targetDuration{}; // 指定された時間をFPSに変換する
	std::chrono::time_point<std::chrono::steady_clock> nextFrameTime{};

};