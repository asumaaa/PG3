#include <stdio.h> 

//働く時間Hを指定して給料を計算する関数
template<typename Type>
Type rewardHour(Type hour, Type reward)
{
	return static_cast<Type>(hour * reward);
}

//再帰的な賃金形態の場合、時間を指定して給料を計算する関数
template<typename Type>
Type rewardRecursive(Type hour, Type reward)
{
	if (hour <= 1)
	{
		static_cast<Type>(rewardH * hour)
	}
	return static_cast<Type>(rewardRecursive(Type hour, Type reward));
}

int main()
{
	int rewardH = 1072;//時給
	int rewardR = 100;//再帰的な賃金形態の場合の時給

	printf("%d\n", rewardHour<int>(3, rewardH));
	printf("%d\n",rewardHour<int>(3, rewardH));

	return 0;
}