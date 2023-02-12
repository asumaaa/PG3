#include "DxLib.h"
#include "TaskManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{

	char key[256];
	char oldKey[256] = { 0 };

	const int WindowWidth = 1024;
	const int WindowHeight = 576; 

	ChangeWindowMode(true);
	SetGraphMode(WindowWidth, WindowHeight, 32);
	SetBackgroundColor(256, 256, 256);
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	TaskManager* taskManager = nullptr;
	taskManager = TaskManager::GetInstance();
	taskManager->Initialize();

	//ƒQ[ƒ€ƒ‹[ƒv
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		GetHitKeyStateAll(key);
		ClearDrawScreen();

		taskManager->Update();
		taskManager->Draw();

		//oldkey‚ðŽæ“¾
		memcpy(oldKey, key, sizeof(key));
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}