#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <functional> 
#include <windows.h> 

int main()
{
	//�T�C�R���𐶐�
	srand(time(nullptr));
	int diceNum = rand() % 6 + 1;

	//���[�U�[���T�C�R���̏o�ڂ�\�z
	int inputNum = 0;
	printf("�T�C�R���̏o�ڂ�����������\�z���Ă�������\n");
	printf("��̏ꍇ:1 �����̏ꍇ:2\n");
	scanf_s("%d",&inputNum);

	int waitTime = 3000;	//�҂��ԁi�~���b�j

	//�w�肵�����ԑ҂�
	Sleep(waitTime);
	//�������Ԃ��֐�
	std::function<int(int)> judge = [=](int i) {return i % 2; };

	//�����肩���肷��
	if (inputNum == 1)
	{
		if (judge(diceNum) == 0)
		{
			printf("�͂���I\n");
		}
		else
		{
			printf("������I\n");
		}
	}
	else if (inputNum == 2)
	{
		if (judge(diceNum) == 1)
		{
			printf("�͂���I\n");
		}
		else
		{
			printf("������I\n");
		}
	}
	else
	{
		printf("���������͂��Ă�������\n");
	}

	return 0;
}