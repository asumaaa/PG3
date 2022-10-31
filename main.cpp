#include <stdio.h> 
#include <stdlib.h>  
#include "vector"  
#include "list"
#include <iostream>
#include <windows.h> 

int main()
{
	//1970�N�̎R������`
	std::list<const char*> station =
	{
		"Tokyo","Yurakucho","Shimbashi","Hamamatsucho",
		"Tamachi","Shinagawa","Osaki","Gotanda","Meguro",
		"Shibuya","Harajuku","Yoyogi","Shinjuku",
		"Shin-Okubo","Takadanobaba","Mejiro","Ikebukuro",
		"Otsuka","Sugamo","Komagome","Nippori","Uguisudani",
		"Ueno","Okachimachi","Akihabara","Kanda"
	};

	//1970�N�̉w����\��
	printf("1970�N�̎R����̉w�𓌋���������ŕ\��\n");
	for (std::list<const char*>::iterator it = station.begin(); it != station.end(); it++)
	{
		std::cout << *it << std::endl;
	}

	//���闢�̑O�ɐ����闢��ǉ�
	for (std::list<const char*>::iterator it = station.begin(); it != station.end(); it++)
	{
		if (*it == "Nippori")
		{
			it = station.insert(it, "Nishi-Nippori");
			it++;
		}
	}

	//2019�N�̉w����ǉ�
	printf("\n2019�N�̎R����̉w�𓌋���������ŕ\��\n");
	for (std::list<const char*>::iterator it = station.begin(); it != station.end(); it++)
	{
		std::cout << *it << std::endl;
	}

	//�i��̑O�ɍ��փQ�[�g�E�F�C��ǉ�
	for (std::list<const char*>::iterator it = station.begin(); it != station.end(); it++)
	{
		if (*it == "Shinagawa")
		{
			it = station.insert(it, "Takanawa-Gateway");
			it++;
		}
	}

	//2022�N�̉w����ǉ�
	printf("\n2022�N�̎R����̉w�𓌋���������ŕ\��\n");
	for (std::list<const char*>::iterator it = station.begin(); it != station.end(); it++)
	{
		std::cout << *it << std::endl;
	}

	system("pause");

	return 0;
}