#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <windows.h> 

typedef void (*pFunc)(int*,int*);

//サイコロと予想を判定する関数
void Judge(int *diceNum ,int* inputNum)
{
	printf("サイコロの出目は%d:",*diceNum);
	if (*diceNum % 2 == 0)
	{
		printf("偶数です\n");
	}
	else
	{
		printf("奇数です\n");
	}

	//1か2が入力されていたら
	if (*inputNum == 1 || *inputNum == 2)
	{
		if (*inputNum == 1)
		{
			if (*diceNum % 2 == 0)
			{
				printf("はずれ！\n");
			}
			else
			{
				printf("あたり！\n");
			}
		}
		if (*inputNum == 2)
		{
			if (*diceNum % 2 == 1)
			{
				printf("はずれ！\n");
			}
			else
			{
				printf("あたり！\n");
			}
		}
	}
	//それ以外が入力された場合
	else
	{
		printf("正しく入力してください\n");
	}
}

//指定した時間待って関数を実行する関数
void setTimer(pFunc p,int second, int diceNum, int inputNum)
{
	//指定した時間待つ
	Sleep(second);
	
	p(&diceNum,&inputNum);
}

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
	pFunc p;
	p = Judge;
	setTimer(p, waitTime, diceNum,inputNum);

	return 0;
}