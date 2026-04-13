#pragma once

// エントリーポイントとゲームループや初期化などを分離し可読性を項上させるクラス
class Application
{
public:
	// コンストラクタ
	Application();
	// デストラクタ : Dxlibの終了処理等を受け持つ
	~Application();

	// コピーコンストラクタの禁止
	Application(const Application& _other) = delete;
	// コピー代入の禁止
	Application& operator =(const Application& _other) = delete;

	// ウィンドウの設定や3D関連の設定、Dxlibの初期化を行う
	bool Initialize();

	// ゲームループを行う
	void Run();
private:
	// 入力やオブジェクト更新
	void Update();
	// 画面のクリアやオブジェクト描画、画面フリップを行う
	void Draw();

private:


};