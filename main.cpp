#include <stdio.h> 
#include <stdlib.h>  
#include "vector"  
#include "list"
#include <iostream>
#include <windows.h> 

//図書カード構造体
struct Station
{
	int val;
	char name[20];		//氏名
	struct Station* prev;
	struct Station* next;
};

void Create(Station* currentStation,const char *name);
void Index(Station* Station);
void IndexReturn(Station* Station);
Station *GetInsertListAddress(Station* Station,int iterator);

int main()
{
	//駅名定義
	const char* KeihinTohokuStation[] =
	{
		"Omiya","Saitama-Shintoshin","Yono","Kita-Urawa","Urawa","Minami-Urawa",
		"Warabi","Nishi-Kawaguchi","Kawaguchi","Akabane","Higashi-Jujo","Oji",
		"Kami-Nakazato","Tabata","Nishi-Nippori","Nippori","Uguisudani","Ueno",
		"Okachimachi","Akihabara","Kanda","Tokyo","Yurakucho","Shimbashi",
		"Hamamatsucho","Tamachi","Shinagawa","Oimachi","Omori","Kamata",
		"Kawasaki","Tsurumi","Shin-Koyasu","Higashi-Kanagawa","Yokohama",
	};

	int iterator = 0;	
	int stationVal = 35;
	Station *station;

	//先頭のアドレス
	Station headStation;
	headStation.next = nullptr;
	headStation.prev = nullptr;

	//高輪ゲートウェイ追加前の駅を代入
	for (int i = 0; i < stationVal; i++)
	{
		station = GetInsertListAddress(&headStation, i);
		Create(station, KeihinTohokuStation[i]);
	}

	//アドレスを戻す
	station = GetInsertListAddress(&headStation, 0);
	printf("高輪ゲートウェイ追加前の京浜東北線の駅を上りで表示\n");
	//表示
	Index(station);
	printf("\n");

	//アドレスを横浜に合わせる
	station = GetInsertListAddress(&headStation, stationVal);
	printf("高輪ゲートウェイ追加前の京浜東北線の駅を下りで表示\n");
	//表示
	IndexReturn(station);

	//高輪ゲートウェイ追加後
	stationVal += 1;
	//駅代入
	for (int i = 0; i < stationVal; i++)
	{
		station = GetInsertListAddress(&headStation, i);
		if (i < 27)
		{
			Create(station, KeihinTohokuStation[i]);
		}
		else if (i == 27)
		{
			Create(station, "TakanawaGateway");
		}
		else
		{
			Create(station, KeihinTohokuStation[i - 1]);
		}
	}

	//アドレスを戻す
	station = GetInsertListAddress(&headStation, 0);
	printf("高輪ゲートウェイ追加後の京浜東北線の駅を上りで表示\n");
	//表示
	Index(station);
	printf("\n");

	//アドレスを横浜に合わせる
	station = GetInsertListAddress(&headStation, stationVal);
	printf("高輪ゲートウェイ追加後の京浜東北線の駅を下りで表示\n");
	//表示
	IndexReturn(station);

	system("pause");
	return 0;
}

void Create(Station* currentStation, const char* name)
{
	Station* newStation;
	newStation = (Station*)malloc(sizeof(Station));

	strcpy_s(newStation->name, 20, name);
	newStation->prev = currentStation;
	newStation->next = currentStation->next;

	if (currentStation->next)
	{
		Station* nextStation = currentStation->next;
		nextStation->prev = newStation;
	}
	currentStation->next = newStation;
}

void Index(Station* Station)
{
	while (Station->next != nullptr)
	{
		Station = Station->next;
		printf("%s\n", Station->name);
	}
}
void IndexReturn(Station* Station)
{
	while (Station->prev != nullptr)
	{
		printf("%s\n", Station->name);
		Station = Station->prev;
	}
}

Station *GetInsertListAddress(Station* Station, int iterator)
{
	for (int i = 0; i < iterator; i++)
	{
		if (Station->next)
		{
			Station = Station->next;
		}
		else
		{
			break;
		}
	}
	return Station;
}
