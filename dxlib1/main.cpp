#include "DxLib.h"
#include "memory"
#include "list"
#include "vector"
#include "math.h"
#include "DirectXMath.h"

#define PI 3.141592653589;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{

	char key[256];
	char oldKey[256] = { 0 };

	const int WindowWidth = 1024;
	const int WindowHeight = 576; 

	ChangeWindowMode(true);
	SetGraphMode(WindowWidth, WindowHeight, 32);
	SetBackgroundColor(0, 0, 0);
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	//線を描画するための点
	size_t dotVol = 50;
	std::vector<DirectX::XMFLOAT2>dot;
	dot.resize(dotVol);

	//始点終点
	DirectX::XMFLOAT2 startPos(0, WindowHeight / 2);
	DirectX::XMFLOAT2 endPos(0, WindowWidth / 2);

	float addX = WindowWidth / dotVol;
	//点の初期数値定義
	for (int i = 0; i < dot.size(); i++)
	{
		dot[i].x = addX * i;
		dot[i].y = WindowHeight / 2;
	}

	float timer = 0;

	//ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		GetHitKeyStateAll(key);
		ClearDrawScreen();

		//更新
		timer++;

		float addPI = PI;
		addPI /= 8;
		float addPI2;

		for (int i = 0; i < dot.size(); i++)
		{
			float i2 = timer + i;
			if (i2 >= 50)
			{
				i2 -= 50;
			}

			addPI2 = addPI * i2;

			dot[i].y = 300 + (cos(addPI2) * 100);
		}

		if (timer >= 49)
		{
			timer = 0;
		}

		//描画
		for (int i = 0; i < dot.size() - 1; i++)
		{
			if(i != 0)DrawLine(dot[i].x, dot[i].y, dot[i + 1].x, dot[i + 1].y, 0xffffff);
		}

		//oldkeyを取得
		memcpy(oldKey, key, sizeof(key));
		ScreenFlip();
	}

	DxLib_End();
	return 0;
}