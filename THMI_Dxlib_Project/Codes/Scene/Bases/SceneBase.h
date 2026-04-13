#pragma once
#include "SceneConstant/SceneConstant.h"

// 各シーンの基底となるクラス
class SceneBase
{
public:
	SceneBase() = default;
	virtual ~SceneBase() = default;

	// シーン内の状況を更新する関数
	SceneType Update()
	{
		switch (currentStep)
		{
		case SceneStep::None: // 未定義
			break;
		case SceneStep::Initialize: // 切り替え時
			Initialize();
			break;
		case SceneStep::Execute: // 実行中
			Execute();
			break;
		case SceneStep::Terminate: // 終了時処理
			return Terminate(); // ここではシーン終了処理となるためretrunで処理を抜ける
		}

		return GetType(); // 自分のシーンを返す
	}

	// そのシーンのExecute時に回る物理処理
	void FixedUpdate()
	{
		if (currentStep == SceneStep::Execute)
		{
			FixedExecute();
		}
	}

	// 描画関数
	virtual void Draw() = 0;
	// 各シーンの種類を返すGetter
	virtual SceneType GetType() = 0;

protected:
	virtual void Initialize() = 0; // 切り替え時処理
	virtual void Execute() = 0; // 実行中処理
	virtual void FixedExecute() = 0; // 物理処理
	virtual SceneType Terminate() = 0; // シーンを抜けるときの処理 : 戻り値として次のシーンを返す

protected:
	SceneStep currentStep{ SceneStep::Initialize }; // シーンの状況を保持するメンバ

};