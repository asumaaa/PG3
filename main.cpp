#include <stdio.h> 

//��������H���w�肵�ċ������v�Z����֐�
template<typename Type>
Type rewardHour(Type hour, Type reward)
{
	return static_cast<Type>(hour * reward);
}

//�ċA�I�Ȓ����`�Ԃ̏ꍇ�A���Ԃ��w�肵�ċ������v�Z����֐�
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
	int rewardH = 1072;//����
	int rewardR = 100;//�ċA�I�Ȓ����`�Ԃ̏ꍇ�̎���

	printf("%d\n", rewardHour<int>(3, rewardH));
	printf("%d\n",rewardHour<int>(3, rewardH));

	return 0;
}