#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <functional> 
#include <windows.h> 

int main()
{
	//サイコロを生成
	srand(time(nullptr));

	//ユーザーがサイコロの出目を予想
	int inputNum = 0;
	printf("サイコロの出目が奇数か偶数か予想してください\n");
	printf("奇数の場合:0 偶数の場合:1\n");
	scanf_s("%d",&inputNum);

	int waitTime = 3;	//待つ時間

	//奇数偶数を返す関数
	std::function<void()> judge = [=]()
	{
		if (inputNum == 0 || inputNum == 1)
		{
			if (rand() % 2 == inputNum)printf("あたり！\n");
			if (rand() % 2 != inputNum)printf("はずれ！\n");
		}
		else{printf("正しく入力してください\n");}
	};

	//タイムアウト関数
	std::function<void(std::function<void()>, int)> setTimeOut = [](std::function<void()> fx, int sec) {fx(), Sleep(sec * 1000); };

	//指定した時間待つ
	setTimeOut(judge, waitTime);
	judge();

	return 0;
}