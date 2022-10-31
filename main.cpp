#include <stdio.h> 
#include <stdlib.h>  
#include "vector"  
#include "list"
#include <iostream>
#include <windows.h> 

//図書カード構造体
struct LibraryCard
{
	char name[20];		//氏名
	int lendDay;	//貸出日
	int returnDay;	//返却日
	struct LibraryCard* next;
};

//図書カードの名前、貸出返却日を保存する関数
void create(LibraryCard* libraryCard, const char* buf,int lend,int re);
//図書カードの一覧を表示する関数
void index(LibraryCard* libraryCard);

int main()
{
	LibraryCard user;
	user.next = nullptr;

	create(&user, "tanaka",20220104, 20220114);
	create(&user, "yamada", 20220204, 20220214);

	index(&user);

	system("pause");

	return 0;
}

//図書カードの名前、貸出返却日を保存する関数
void create(LibraryCard* libraryCard, const char* buf, int lend, int re)
{
	LibraryCard* newLibraryCard;
	//図書カードを新規作成
	newLibraryCard = (LibraryCard*)malloc(sizeof(LibraryCard));

	strcpy_s(newLibraryCard->name, 20, buf);
	newLibraryCard->lendDay = lend;
	newLibraryCard->returnDay = re;
	newLibraryCard->next = nullptr;

	//追加する前の最後尾を検索
	while (libraryCard->next != nullptr)
	{
		libraryCard = libraryCard->next;
	}

	//最後尾に新規作成した図書カードのポインタを代入
	libraryCard->next = newLibraryCard;
}

//図書カードの一覧を表示する関数
void index(LibraryCard* libraryCard)
{
	while (libraryCard->next != nullptr)
	{
		libraryCard = libraryCard->next;

		printf("氏名:%s 貸出日:%d 返却日:%d\n",
			libraryCard->name, libraryCard->lendDay, libraryCard->returnDay);
	}
}