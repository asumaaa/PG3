#pragma once

////構造体
//struct Object
//{
//	int val;
//	char name[20];		//氏名
//	struct Object* prev;
//	struct Object* next;
//};
//
//class List
//{
//private:
//	List();
//	~List();
//public:
//	static List* GetInstance();
//private:
//	//リスト
//	Object* object;
//
//	//イテレータ
//	int iterator = 0;
//	int objectVal;
//
//	//先頭のアドレス
//	Object *headObject = nullptr;
//public:
//	//双方向リストの操作
//	void Create(const char* name,int val);
//	void Index();
//	/*void IndexReturn();*/
//	Object* GetInsertListAddress(int val);
//};


struct Object
{
	int val;
	char name[20];		//氏名
	struct Object* prev;
	struct Object* next;
};

class List
{
public:
	void Create( const char* name,int objectVal);
	void Index(Object* Station);
	void IndexReturn(Object* Station);
	Object* GetInsertListAddress(Object* object,int num);
private:
	int iterator = 0;
	int objectVal = 35;
	Object* object;

	//先頭のアドレス
	Object headObject;
};
