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

	int waitTime = 3;	//�҂���

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

	//�^�C���A�E�g�֐�
	std::function<void(std::function<void()>, int)> setTimeOut = [](std::function<void()> fx, int sec) {fx(), Sleep(sec * 1000); };

	//�w�肵�����ԑ҂�
	setTimeOut(judge, waitTime);
	judge();

	return 0;
}