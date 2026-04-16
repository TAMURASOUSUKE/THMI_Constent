#pragma once

// 時間情報を提供するためのインターフェース
class TimeProvider
{
public:
	virtual ~TimeProvider() = default;
	virtual float GetDeltaTime() const = 0;
	virtual float GetFixedDeltaTime() const = 0;
	virtual float GetCurrentFPS() const = 0;
	virtual float GetAlpha() const = 0;
};