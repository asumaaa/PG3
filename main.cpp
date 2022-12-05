#include <stdio.h> 
#include <stdlib.h>  
#include "vector"  
#include "list"
#include <iostream>
#include <windows.h> 
#include <algorithm> 
#include<fstream>
#include "sstream"
#include "Enemy.h"

int Enemy::EnemyCount;
int main()
{
	//敵の数
	const int EnmeyNum = 4;

	Enemy* enemy[EnmeyNum];

	for (int i = 0; i < EnmeyNum; i++)
	{
		enemy[i] = new Enemy;
	}

	printf("敵の数:%d\n", Enemy::EnemyCount);

	int Num;
	while (true)
	{
		printf("1で敵を1体倒す\n");
		scanf_s("%d", &Num);
		//すべての敵のメモリを削除
		if (Num == 1)
		{
			for (int i = 0; i < EnmeyNum; i++)
			{
				delete enemy[i];
			}
			break;
		}
		printf("失敗した...\n");
	}

	printf("敵の数:%d\n", Enemy::EnemyCount);

	system("pause");
	return 0;
}