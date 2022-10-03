#include <stdio.h> 

//働く時間Hを指定して給料を計算する関数
int rewardHour(int hour, int reward)
{
	return hour * reward;
}

//再帰的な賃金形態の場合の時間を指定しての給料を計算
int rewardRecursive(int hour, int reward)
{
	if (hour < 1)
	{
		return 100;
	}

	return rewardRecursive(hour - 1, reward) * 2 - 50;
}

//再帰的な賃金形態の場合の給料の合計を計算
int rewardRecursiveSum(int hour,int reward)
{
	int rewardTotal = 0;
	for (int i = 0; i < hour; i++)
	{
		rewardTotal += rewardRecursive(i, reward);
	}

	return rewardTotal;
}

int main()
{
	int rewardH = 1072;//時給
	int rewardR = 100;//再帰的な賃金形態の場合の時給

	for (int i = 0; i < 100; i++)
	{
		printf("%d時間働いた場合\n", i);
		printf("一般的な賃金体態:%d円\n", rewardHour(i, rewardH));
		printf("再起的な賃金体態:%d円\n\n", rewardRecursiveSum(i, rewardR));
		if (rewardHour(i, rewardH) < rewardRecursiveSum(i, rewardR))
		{
			break;
		}
	}

	return 0;
}