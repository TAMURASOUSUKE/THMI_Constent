#include "TimeManager.h"

const ITimeReader* TimeManager::readerProvider = nullptr;
ITimeController* TimeManager::controllerProvider = nullptr;

void TimeManager::SetProvider(const ITimeReader* _provider, ITimeController* _controllerProvider)
{
	readerProvider = _provider;
	controllerProvider = _controllerProvider;
}

void TimeManager::SetTimeScale(const float _scale)
{
	// 登録されているか確認
	if (controllerProvider)
	{
		controllerProvider->SetTimeScale(_scale);
	}
}

float TimeManager::DeltaTime()
{
	// プロバイダーが登録されているかのチェックを入れる
	return readerProvider ? readerProvider->GetDeltaTime() : 0.0f;
}

float TimeManager::UnscaledDeltaTime()
{
	// プロバイダーが登録されているかのチェックを入れる
	return readerProvider ? readerProvider->GetUnscaledDeltaTime() : 0.0f;
}

float TimeManager::FixedDeltaTime()
{
	// プロバイダーが登録されているかのチェックを入れる
	return readerProvider ? readerProvider->GetFixedDeltaTime() : 0.0f;
}

float TimeManager::Alpha()
{
	// プロバイダーが登録されているかのチェックを入れる
	return readerProvider ? readerProvider->GetAlpha() : 0.0f;
}


float TimeManager::GetCurrentFPS()
{
	// プロバイダーが登録されているかのチェックを入れる
	return readerProvider ? readerProvider->GetCurrentFPS() : 0.0f;
}

float TimeManager::GetTimeScale()
{
	// プロバイダーが登録されているかのチェックを入れる
	return readerProvider ? readerProvider->GetTimeScale() : 0.0f;
}