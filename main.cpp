#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <functional> 
#include <windows.h> 

int main()
{
	//サイコロを生成
	srand(time(nullptr));
	int diceNum = rand() % 6 + 1;

	//ユーザーがサイコロの出目を予想
	int inputNum = 0;
	printf("サイコロの出目が奇数か偶数か予想してください\n");
	printf("奇数の場合:1 偶数の場合:2\n");
	scanf_s("%d",&inputNum);

	int waitTime = 3000;	//待つ時間（ミリ秒）

	//指定した時間待つ
	Sleep(waitTime);
	//奇数偶数を返す関数
	std::function<int(int)> judge = [=](int i) {return i % 2; };

	//当たりか判定する
	if (inputNum == 1)
	{
		if (judge(diceNum) == 0)
		{
			printf("はずれ！\n");
		}
		else
		{
			printf("あたり！\n");
		}
	}
	else if (inputNum == 2)
	{
		if (judge(diceNum) == 1)
		{
			printf("はずれ！\n");
		}
		else
		{
			printf("あたり！\n");
		}
	}
	else
	{
		printf("正しく入力してください\n");
	}

	return 0;
}