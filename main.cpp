#include <stdio.h> 
#include <stdlib.h>  
#include "vector"  
#include "list"
#include <iostream>
#include <windows.h> 

int main()
{
	//1970年の山手線を定義
	std::list<const char*> station =
	{
		"Tokyo","Yurakucho","Shimbashi","Hamamatsucho",
		"Tamachi","Shinagawa","Osaki","Gotanda","Meguro",
		"Shibuya","Harajuku","Yoyogi","Shinjuku",
		"Shin-Okubo","Takadanobaba","Mejiro","Ikebukuro",
		"Otsuka","Sugamo","Komagome","Nippori","Uguisudani",
		"Ueno","Okachimachi","Akihabara","Kanda"
	};

	//1970年の駅名を表示
	printf("1970年の山手線の駅を東京から内回りで表示\n");
	for (std::list<const char*>::iterator it = station.begin(); it != station.end(); it++)
	{
		std::cout << *it << std::endl;
	}

	//日暮里の前に西日暮里を追加
	for (std::list<const char*>::iterator it = station.begin(); it != station.end(); it++)
	{
		if (*it == "Nippori")
		{
			it = station.insert(it, "Nishi-Nippori");
			it++;
		}
	}

	//2019年の駅名を追加
	printf("\n2019年の山手線の駅を東京から内回りで表示\n");
	for (std::list<const char*>::iterator it = station.begin(); it != station.end(); it++)
	{
		std::cout << *it << std::endl;
	}

	//品川の前に高輪ゲートウェイを追加
	for (std::list<const char*>::iterator it = station.begin(); it != station.end(); it++)
	{
		if (*it == "Shinagawa")
		{
			it = station.insert(it, "Takanawa-Gateway");
			it++;
		}
	}

	//2022年の駅名を追加
	printf("\n2022年の山手線の駅を東京から内回りで表示\n");
	for (std::list<const char*>::iterator it = station.begin(); it != station.end(); it++)
	{
		std::cout << *it << std::endl;
	}

	system("pause");

	return 0;
}