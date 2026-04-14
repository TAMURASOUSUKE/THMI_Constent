#include "DxLib.h"
#include "Codes/Application/Application.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Application app{}; // ゲームループを持つクラスのインスタンス

	// falseが返ると初期化に失敗したとみなし-1を返す
	if (!app.Initialize())
	{
		return -1;
	}

	// ゲームループの開始
	app.Run();

	return 0;				// ソフトの終了 
}