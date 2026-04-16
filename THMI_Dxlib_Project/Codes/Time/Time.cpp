#include "Time.h"

void Time::SetProvider(const ITimeReader* _provider, ITimeController* _controllerProvider)
{
	readerProvider = _provider;
	controllerProvider = _controllerProvider;
}

void Time::SetTimeScale(const float _scale)
{
	// 登録されているか確認
	if (controllerProvider)
	{
		controllerProvider->SetTimeScale(_scale);
	}
}

float Time::DeltaTime()
{
	// プロバイダーが登録されているかのチェックを入れる
	return readerProvider ? readerProvider->GetDeltaTime() : 0.0f;
}

float Time::UnscaledDeltaTime()
{
	// プロバイダーが登録されているかのチェックを入れる
	return readerProvider ? readerProvider->GetUnscaledDeltaTime() : 0.0f;
}

float Time::FixedDeltaTime()
{
	// プロバイダーが登録されているかのチェックを入れる
	return readerProvider ? readerProvider->GetFixedDeltaTime() : 0.0f;
}

float Time::Alpha()
{
	// プロバイダーが登録されているかのチェックを入れる
	return readerProvider ? readerProvider->GetAlpha() : 0.0f;
}


float Time::GetCurrentFPS()
{
	// プロバイダーが登録されているかのチェックを入れる
	return readerProvider ? readerProvider->GetCurrentFPS() : 0.0f;
}

float Time::GetTimeScale()
{
	// プロバイダーが登録されているかのチェックを入れる
	return readerProvider ? readerProvider->GetTimeScale() : 0.0f;
}