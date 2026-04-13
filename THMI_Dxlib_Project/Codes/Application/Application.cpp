#include <windows.h>
#include <timeapi.h> // 高精度タイマーを使うため
#include <Dxlib.h>
#include "Application.h"

#pragma comment(lib, "winmm.lib") // 高精度タイマーを使うためのリンカ接続

Application::Application()
{
	timeBeginPeriod(1); //　タイマーの解像度を1msに上げる溜めに使う
}

Application::~Application()
{
	timeEndPeriod(1); // タイマーの解像度を元に戻す
	DxLib_End(); // Dxlibの終了処理
}

bool Application::Initialize()
{
	// 画面サイズの決定
	SetGraphMode(1920, 1080, 32);

	// ウィンドウモードの設定(デバッグモードの時はウィンドウモードでそれ以外の時は全画面になります)
#ifdef _DEBUG
	ChangeWindowMode(true);
#else
	ChangeWindowMode(false);
#endif // _DEBUG

	// 初期化に失敗するとfalseを返す
	if (DxLib_Init() == -1)
	{
		return false;
	}

	SetDrawScreen(DX_SCREEN_BACK); // 描画バッファをバックバッファに設定
	SetUseBackCulling(true); // 背面のカリングを有効化
	SetUseZBuffer3D(true); // Zバッファを有効化
	SetWriteZBuffer3D(true); // Zバッファへの書き込みを有効化
	SetUseLighting(true); // ライトを有効化
	SetCameraNearFar(1.0f, 10000.0f); // カメラのクリップ距離を設定

	// ここまでくると成功と判断しtrue
	return true;
}

void Application::Run()
{
	// ゲームループを実装(プロセスメッセージが失敗するかESCが押されるまでループ)
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		Update(); // 更新処理
		Draw(); // 描画処理
	}
}

void Application::Draw()
{
	ClearDrawScreen(); // 画面のクリア

	ScreenFlip(); // 画面のフリップ
}