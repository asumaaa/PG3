#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <functional> 
#include <windows.h> 

int main()
{
	//�T�C�R���𐶐�
	srand(time(nullptr));

	//���[�U�[���T�C�R���̏o�ڂ�\�z
	int inputNum = 0;
	printf("�T�C�R���̏o�ڂ�����������\�z���Ă�������\n");
	printf("��̏ꍇ:0 �����̏ꍇ:1\n");
	scanf_s("%d",&inputNum);

	int waitTime = 3000;	//�҂��ԁi�~���b�j

	//�������Ԃ��֐�
	std::function<void()> judge = [=]()
	{
		if (inputNum == 0 || inputNum == 1)
		{
			if (rand() % 2 == inputNum)printf("������I\n");
			if (rand() % 2 != inputNum)printf("�͂���I\n");
		}
		else{printf("���������͂��Ă�������\n");}
	};

	//�w�肵�����ԑ҂�
	Sleep(waitTime);
	judge();

	////�����肩���肷��
	//if (inputNum == 1)
	//{
	//	if (judge(diceNum) == 0)
	//	{
	//		printf("�͂���I\n");
	//	}
	//	else
	//	{
	//		printf("������I\n");
	//	}
	//}
	//else if (inputNum == 2)
	//{
	//	if (judge(diceNum) == 1)
	//	{
	//		printf("�͂���I\n");
	//	}
	//	else
	//	{
	//		printf("������I\n");
	//	}
	//}
	//else
	//{
	//	printf("���������͂��Ă�������\n");
	//}

	return 0;
}