#include "SystemConstant/SystemConstant.h"
#include "FrameRateCounter.h"

void FrameRateCounter::Update(const time_point<steady_clock>& _currentTime)
{
	// 初期化処理 最初に呼び出されたときに引数の時間をstarTimeとして設定する
	if (frameCounter == 0 && startTime.time_since_epoch().count() == 0)
	{
		startTime = _currentTime;
	}

	// 開始時刻から現在の時刻までを求めそれをマイクロ秒に変換する
	auto elapsedTime{ duration_cast<microseconds>(_currentTime - startTime).count() };

	// 現在のFPS計算処理
	if (frameCounter == SAMPLE_FRAME_COUNT) // 計測器がサンプル用FPSまで到達したら
	{
		if (elapsedTime > 0) // 時間が経過していたら
		{
			// 現在のFPS = 目標値のFPS * 100,000,000 / 経過時間(マイクロ秒)
			currentFPS = static_cast<float>(frameCounter) * ONE_SEC_MICRO / static_cast<float>(elapsedTime);
		}

		// リセット処理
		frameCounter = 0;
		startTime = _currentTime;
	}

}