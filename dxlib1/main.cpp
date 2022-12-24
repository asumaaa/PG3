#include "DxLib.h"
#include "GameScene.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	const int WindowWidth = 1024;
	const int WindowHeight = 576; 

	ChangeWindowMode(true);
	SetGraphMode(WindowWidth, WindowHeight, 32);
	SetBackgroundColor(0, 0, 0);
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	//ゲームシーン生成
	GameScene* gameScene = nullptr;
	gameScene = new GameScene();
	gameScene->Initialize();

	//ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//画面クリア
		ClearDrawScreen();

		//更新処理
		gameScene->Update();

		//描画処理
		gameScene->Draw();

		ScreenFlip();
	}

	delete gameScene;

	DxLib_End();
	return 0;
}