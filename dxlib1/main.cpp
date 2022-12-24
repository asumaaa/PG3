#include "DxLib.h"
#include "Enemy.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{

	char key[256];
	char oldKey[256] = { 0 };

	const int WindowWidth = 1024;
	const int WindowHeight = 576; 
	//�G
	Enemy* enemy = new Enemy(100, 100);

	ChangeWindowMode(true);
	SetGraphMode(WindowWidth, WindowHeight, 32);
	SetBackgroundColor(0, 0, 64);
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	//�Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		GetHitKeyStateAll(key);
		ClearDrawScreen();

		//�G�̍X�V
		enemy->Update();

		//�G�̕`��
		enemy->Draw();

		//oldkey���擾
		memcpy(oldKey, key, sizeof(key));
		ScreenFlip();
	}
	delete enemy;

	DxLib_End();
	return 0;
}