#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <windows.h> 

typedef void (*pFunc)(int*,int*);

//�T�C�R���Ɨ\�z�𔻒肷��֐�
void Judge(int *diceNum ,int* inputNum)
{
	printf("�T�C�R���̏o�ڂ�%d:",*diceNum);
	if (*diceNum % 2 == 0)
	{
		printf("�����ł�\n");
	}
	else
	{
		printf("��ł�\n");
	}

	//1��2�����͂���Ă�����
	if (*inputNum == 1 || *inputNum == 2)
	{
		if (*inputNum == 1)
		{
			if (*diceNum % 2 == 0)
			{
				printf("�͂���I\n");
			}
			else
			{
				printf("������I\n");
			}
		}
		if (*inputNum == 2)
		{
			if (*diceNum % 2 == 1)
			{
				printf("�͂���I\n");
			}
			else
			{
				printf("������I\n");
			}
		}
	}
	//����ȊO�����͂��ꂽ�ꍇ
	else
	{
		printf("���������͂��Ă�������\n");
	}
}

//�w�肵�����ԑ҂��Ċ֐������s����֐�
void setTimer(pFunc p,int second, int diceNum, int inputNum)
{
	//�w�肵�����ԑ҂�
	Sleep(second);
	
	p(&diceNum,&inputNum);
}

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
	pFunc p;
	p = Judge;
	setTimer(p, waitTime, diceNum,inputNum);

	return 0;
}