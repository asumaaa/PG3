#include <stdio.h> 
#include <stdlib.h>  
#include "vector"  
#include "list"
#include <iostream>
#include <windows.h> 

//struct CELL
//{
//	int val;
//	struct CELL* next;
//};
//
////セルを新規作成する関数
//void create(CELL* cell, int num);
////セルの一覧を表示する関数
//void index(CELL* cell);
//
//int main()
//{
//	CELL head;
//	head.next = nullptr;
//
//	create(&head, 4);
//	create(&head, 6);
//
//	index(&head);
//
//	system("pause");
//
//	return 0;
//}
//
////セルを新規作成する関数
//void create(CELL* cell, int num)
//{
//	CELL* newCell;
//	//セルを新規作成
//	newCell = (CELL*)malloc(sizeof(CELL));
//	newCell->val = num;
//	newCell->next = nullptr;
//
//	//追加する前の最後尾を検索
//	while (cell->next != nullptr)
//	{
//		cell = cell->next;
//	}
//
//	//最後尾に新規作成したセルのポインタを代入
//	cell->next = newCell;
//}
//
////セルの一覧を表示する関数
//void index(CELL* cell)
//{
//	int i = 0;
//	while (cell->next != nullptr)
//	{
//		i++;
//		cell = cell->next;
//
//		printf("%d番目のセルの値:%d\n", i,cell->val);
//	}
//}

struct CELL
{
	char str[20];
	struct CELL* next;
};

//セルを新規作成する関数
void create(CELL* cell, const char* buf);
//セルの一覧を表示する関数
void index(CELL* cell);

int main()
{
	CELL head;
	head.next = nullptr;

	create(&head, "aiueo");
	create(&head, "abcde");

	index(&head);

	system("pause");

	return 0;
}

//セルを新規作成する関数
void create(CELL* cell, const char* buf)
{
	CELL* newCell;
	//セルを新規作成
	newCell = (CELL*)malloc(sizeof(CELL));

	strcpy_s(newCell->str, 20, buf);
	newCell->next = nullptr;

	//追加する前の最後尾を検索
	while (cell->next != nullptr)
	{
		cell = cell->next;
	}

	//最後尾に新規作成したセルのポインタを代入
	cell->next = newCell;
}

//セルの一覧を表示する関数
void index(CELL* cell)
{
	int i = 0;
	while (cell->next != nullptr)
	{
		i++;
		cell = cell->next;

		printf("%d番目のセルの名前:%s\n", i, cell->str);
	}
}