#include <stdio.h> 
#include <stdlib.h>  
#include "vector"  
#include "list"
#include <iostream>
#include <windows.h> 
#include <algorithm> 
#include<fstream>
#include "sstream"

enum class Mode
{
	Initial,
	Display,
	Insert,
	Edit,
	Delete,
	Sort,
};

//最初にリストに入れたい文字列
const char* fruits[] =
{
	"banana","apple","orange"
};

struct Object
{
	int val;
	char name[20];		//氏名
	struct Object* prev;
	struct Object* next;
};

void Create(Object* currentObject, const char* name);
void Change(Object* currentObject, char* name);
void Index(Object* object);
void deleteAddress(Object* object,int num);
Object* GetInsertListAddress(Object* object, int iterator);

void InitialText(int num);	//初期画面のテキスト

void DisplayText1();	//表示画面表示のテキスト1
void DisplayText2();	//表示画面表示のテキスト2

void InsertText();	//挿入画面表示のテキスト

void EditText();	//編集画面表示のテキスト

void DeleteText();	//編集画面表示のテキスト

void Create(Object* currentobject, const char* name);
void Index(Object* object);
void IndexSelect(Object* object,int num);
Object* GetInsertListAddress(Object* object, int iterator);

int main()
{
	//入力に使う変数
	int inputNum;
	//最初のモードは初期画面
	Mode mode = Mode::Initial;
	//要素の現在の数

	int iterator = 0;
	int objectVal = 3;
	//双方向リスト
	Object* food;

	//先頭のアドレス
	Object headObject;
	headObject.next = nullptr;
	headObject.prev = nullptr;

	for (int i = 0; i < objectVal; i++)
	{
		food = GetInsertListAddress(&headObject, i);
		Create(food, fruits[i]);
	}

	while (true)
	{
		//初期画面
		if (mode == Mode::Initial)
		{
			//初期テキスト表示
			InitialText(objectVal);
			//操作入力
			scanf_s("%d", &inputNum);

			//入力によってモード変更
			if (inputNum == 1)mode = Mode::Display;
			else if (inputNum == 2)mode = Mode::Insert;
			else if (inputNum == 3 && objectVal)mode = Mode::Edit;
			else if (inputNum == 4 && objectVal)mode = Mode::Delete;
			else if (inputNum == 5)break;
			else
			{
				printf("正しく入力してください\n");
				mode == Mode::Initial;
			}
		}
		//要素表示画面
		if (mode == Mode::Display)
		{
			//テキスト表示
			DisplayText1();
			//操作入力
			scanf_s("%d", &inputNum);

			//要素の一覧表示
			if (inputNum == 1)
			{
				printf("[要素の一覧表示]\n");
				food = GetInsertListAddress(&headObject, 0);
				Index(food);
			}
			//指定した要素表示
			if (inputNum == 2)
			{
				printf("[要素の指定して要素を表示]\n");
				printf("表示したい要素の順番を指定してください\n");
				//入力に使う変数
				int num;
				scanf_s("%d", &num);
				food = GetInsertListAddress(&headObject, 0);
				IndexSelect(food, num);
			}

			//入力によってモード変更
			while (true)
			{
				//テキスト表示
				DisplayText2();
				scanf_s("%d", &inputNum);
				//正しく入力したら抜ける
				if (inputNum == 1)
				{
					mode = Mode::Display;
					break;
				}
				else if (inputNum == 2)
				{
					mode = Mode::Initial;
					break;
				}
				else
				{
					printf("正しく入力してください\n");
				}
			}
		}
		//要素の挿入
		if (mode == Mode::Insert)
		{
			printf("[要素の編集]\n");
			printf("編集したい要素の番号を指定してください\n");
			printf("入力した番号に要素がない場合1番後ろに追加します\n");
			scanf_s("%d", &inputNum);

			if (inputNum > objectVal)
			{
				inputNum = objectVal;
			}
			food = GetInsertListAddress(&headObject, inputNum);
			printf("%d番目の要素に追加する値を入力してください\n", inputNum);
			char str[20];
			scanf_s("%s", str, 20);

			//要素を変更
			printf("%d番目の要素に%sを追加\n", inputNum,str);
			objectVal++;
			Create(food, str);

			//入力によってモード変更
			while (true)
			{
				//テキスト表示
				InsertText();
				scanf_s("%d", &inputNum);
				//正しく入力したら抜ける
				if (inputNum == 1)
				{
					mode = Mode::Insert;
					break;
				}
				else if (inputNum == 2)
				{
					mode = Mode::Initial;
					break;
				}
				else
				{
					printf("正しく入力してください\n");
				}
			}
		}
		//要素の編集
		if (mode == Mode::Edit)
		{
			/*char str[20];
			scanf_s("%s", str);*/
			printf("[要素の編集]\n");
			printf("編集したい要素の番号を指定してください\n");
			scanf_s("%d", &inputNum);
			
			//入力した番号の要素がない場合
			if (inputNum >= objectVal || inputNum < 0)
			{
				printf("%d番目の要素が見つかりませんでした\n", inputNum);
			}
			//入力した要素の番号がある場合
			else
			{
				food = GetInsertListAddress(&headObject, inputNum + 1);
				printf("%d番目の要素の変更する値を入力してください\n", inputNum);
				char str[20];
				scanf_s("%s", str,20);

				//要素を変更
				printf("%sに値を変更\n",str);
				Change(food, str);
			}
			//入力によってモード変更
			while (true)
			{
				//テキスト表示
				EditText();
				scanf_s("%d", &inputNum);
				//正しく入力したら抜ける
				if (inputNum == 1)
				{
					mode = Mode::Display;
					break;
				}
				else if (inputNum == 2)
				{
					mode = Mode::Initial;
					break;
				}
				else
				{
					printf("正しく入力してください\n");
				}
			}
		}
		//要素の削除
		if (mode == Mode::Delete)
		{
			printf("[要素の削除]\n");
			printf("削除したい要素の番号を指定してください\n");
			scanf_s("%d", &inputNum);

			//入力した番号の要素がない場合
			if (inputNum >= objectVal || inputNum < 0)
			{
				printf("%d番目の要素が見つかりませんでした\n", inputNum);
			}
			else
			{
				objectVal--;
				for (int i = 0; i < objectVal; i++)
				{
					if (i < inputNum)
					{
						food = GetInsertListAddress(&headObject, i);
						Create(food, food->name);
					}
					else
					{
						food = GetInsertListAddress(&headObject, i + 1);
						Create(food, food->name);
					}
				}
			}
			//入力によってモード変更
			while (true)
			{
				//テキスト表示
				DeleteText();
				scanf_s("%d", &inputNum);
				//正しく入力したら抜ける
				if (inputNum == 1)
				{
					mode = Mode::Delete;
					break;
				}
				else if (inputNum == 2)
				{
					mode = Mode::Initial;
					break;
				}
				else
				{
					printf("正しく入力してください\n");
				}
			}
		}
	}

	system("pause");
	return 0;
}

void InitialText(int num)
{
	printf("[要素の操作]\n");
	printf("1.要素の表示\n");
	printf("2.要素の挿入\n");
	if (num > 0)
	{
		printf("3.要素の編集\n");
		printf("4.要素の削除\n");
	}
	printf("5.終了\n");
	printf("\n");
	printf("-------------------------\n");
	printf("操作を選択してください\n");
}

void DisplayText1()
{
	printf("\n");
	printf("[要素の表示]\n");
	printf("1.要素の一覧表示\n");
	printf("2.順番を指定して要素を表示\n");
	printf("9.要素の操作に戻る\n");
	printf("\n");
	printf("-------------------------\n");
	printf("操作を選択してください\n");
}

void DisplayText2()
{
	printf("\n");
	printf("-------------------------\n");
	printf("1.要素の表示に戻る\n");
	printf("2.要素の操作に戻る\n");
}

void InsertText()
{
	printf("\n");
	printf("-------------------------\n");
	printf("1.要素の挿入に戻る\n");
	printf("2.要素の操作に戻る\n");
}

void EditText()
{
	printf("\n");
	printf("-------------------------\n");
	printf("1.要素の編集に戻る\n");
	printf("2.要素の操作に戻る\n");
}

void DeleteText()
{
	printf("\n");
	printf("-------------------------\n");
	printf("1.要素の削除に戻る\n");
	printf("2.要素の操作に戻る\n");
}

void Create(Object* currentObject, const char* name)
{
	Object* newObject;
	newObject = (Object*)malloc(sizeof(Object));

	strcpy_s(newObject->name, 20, name);
	newObject->prev = currentObject;
	newObject->next = currentObject->next;

	if (currentObject->next)
	{
		Object* nextObject = currentObject->next;
		nextObject->prev = newObject;
	}
	currentObject->next = newObject;
}

void Change(Object* currentObject, char* name)
{
	strcpy_s(currentObject->name, 20, name);
}

void Index(Object* object)
{
	int i = 0;
	while (object->next != nullptr)
	{
		object = object->next;
		printf("%d:%s\n", i,object->name);
		i++;
	}
	printf("要素数:%d\n",i);
}

void deleteAddress(Object* object, int num)
{
	Object* newObject;
	newObject = (Object*)malloc(sizeof(Object));

	int i = 0;

	newObject->prev = object->next;
	newObject->next = object->next->next;

	if (object->next)
	{
		Object* nextObject = object->next->next;
		nextObject->prev = newObject;
	}
	object->next = newObject;
}

void IndexSelect(Object* object, int num)
{
	int i = 0;
	while (object->next != nullptr)
	{
		object = object->next;
		if (num == i)
		{
			printf("%s\n",object->name);
		}
		i++;
	}
}

Object* GetInsertListAddress(Object* object, int iterator)
{
	for (int i = 0; i < iterator; i++)
	{
		if (object->next)
		{
			object = object->next;
		}
		else
		{
			break;
		}
	}
	return object;
}