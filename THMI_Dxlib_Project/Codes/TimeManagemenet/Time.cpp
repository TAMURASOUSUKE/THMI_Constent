#include "Time.h"

void Time::SetProvider(const TimeProvider* _provider)
{
	provider = _provider;
}

float Time::DeltaTime()
{
	// プロバイダーが登録されているかのチェックを入れる
	return provider ? provider->GetDeltaTime() : 0.0f;
}

float Time::FixedDeltaTime()
{
	// プロバイダーが登録されているかのチェックを入れる
	return provider ? provider->GetFixedDeltaTime() : 0.0f;
}

float Time::GetCurrentFPS()
{
	// プロバイダーが登録されているかのチェックを入れる
	return provider ? provider->GetCurrentFPS() : 0.0f;
}

float Time::GetAlpha()
{
	// プロバイダーが登録されているかのチェックを入れる
	return provider ? provider->GetAlpha() : 0.0f;
}