#pragma once

// 時間に関する設定機能などを提供するインターフェース
class ITimeController
{
public:
	virtual ~ITimeController() = default;

	virtual void SetTimeScale(const float _scale) = 0; // タイムスケールの設定を行う
};