#include <stdio.h> 

//��������H���w�肵�ċ������v�Z����֐�
int rewardHour(int hour, int reward)
{
	return hour * reward;
}

//�ċA�I�Ȓ����`�Ԃ̏ꍇ�̎��Ԃ��w�肵�Ă̋������v�Z
int rewardRecursive(int hour, int reward)
{
	if (hour < 1)
	{
		return 100;
	}

	return rewardRecursive(hour - 1, reward) * 2 - 50;
}

//�ċA�I�Ȓ����`�Ԃ̏ꍇ�̋����̍��v���v�Z
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
	int rewardH = 1072;//����
	int rewardR = 100;//�ċA�I�Ȓ����`�Ԃ̏ꍇ�̎���

	for (int i = 0; i < 100; i++)
	{
		printf("%d���ԓ������ꍇ\n", i);
		printf("��ʓI�Ȓ����̑�:%d�~\n", rewardHour(i, rewardH));
		printf("�ċN�I�Ȓ����̑�:%d�~\n\n", rewardRecursiveSum(i, rewardR));
		if (rewardHour(i, rewardH) < rewardRecursiveSum(i, rewardR))
		{
			break;
		}
	}

	return 0;
}