#include "DxLib.h"
#include "SceneManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{

	char key[256];
	char oldKey[256] = { 0 };

	const int WindowWidth = 1024;
	const int WindowHeight = 576; 

	ChangeWindowMode(true);
	SetGraphMode(WindowWidth, WindowHeight, 32);
	SetBackgroundColor(0, 0, 64);
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	//�C���X�^���X���擾
	SceneManager* SceneManager = nullptr;
	SceneManager = SceneManager::GetInstance();

	//�V�[��
	SceneManager->SetScene(Title);

	//�Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		GetHitKeyStateAll(key);
		ClearDrawScreen();

		//�X�y�[�X�̃g���K�[�L�[�ŃV�[���`�F���W
		if (key[KEY_INPUT_SPACE] == 1 && oldKey[KEY_INPUT_SPACE] == 0)
		{
			if (SceneManager->GetScene() == Title) {
				SceneManager->ChangeScene(NewGame);
			}
			else if (SceneManager->GetScene() == NewGame) {
				SceneManager->ChangeScene(GamePlay);
			}
			else if (SceneManager->GetScene() == GamePlay) {
				SceneManager->ChangeScene(NewClear);
			}
			else if (SceneManager->GetScene() == NewClear) {
				SceneManager->ChangeScene(Title);
			}
		}

		//�V�[���ɂ���ĐF�`�F���W
		if (SceneManager->GetScene() == Title)SetBackgroundColor(125, 0, 0);
		if (SceneManager->GetScene() == NewGame)SetBackgroundColor(0, 125, 0);
		if (SceneManager->GetScene() == GamePlay)SetBackgroundColor(0, 0, 125);
		if (SceneManager->GetScene() == NewClear)SetBackgroundColor(0, 0, 0);

		//����
		DrawFormatString(0, 0, 0xffffff, "PushSpace");
		DrawFormatString(0, 20, 0xffffff, "Scene:%d", SceneManager->GetScene());

		//oldkey���擾
		memcpy(oldKey, key, sizeof(key));
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}