#pragma once

////�\����
//struct Object
//{
//	int val;
//	char name[20];		//����
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
//	//���X�g
//	Object* object;
//
//	//�C�e���[�^
//	int iterator = 0;
//	int objectVal;
//
//	//�擪�̃A�h���X
//	Object *headObject = nullptr;
//public:
//	//�o�������X�g�̑���
//	void Create(const char* name,int val);
//	void Index();
//	/*void IndexReturn();*/
//	Object* GetInsertListAddress(int val);
//};


struct Object
{
	int val;
	char name[20];		//����
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

	//�擪�̃A�h���X
	Object headObject;
};
