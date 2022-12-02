#include "List.h"
#include <stdio.h> 
#include <stdlib.h>  
#include "vector"  
#include "list"
#include <iostream>
#include <windows.h> 
#include <algorithm> 
#include<fstream>
#include "sstream"

//List::List()
//{
//}
//
//List::~List()
//{
//}
//
//List* List::GetInstance()
//{
//	static List instance;
//	return &instance;
//}
//
//void List::Create(const char* name, int val)
//{
//	this->objectVal = val;
//	object = GetInsertListAddress(objectVal);
//	Object* newObject;
//	newObject = (Object*)malloc(sizeof(Object));
//
//	strcpy_s(newObject->name, 20, name);
//	newObject->prev = object;
//	newObject->next = object->next;
//
//	if (object->next)
//	{
//		Object* nextStation = object->next;
//		nextStation->prev = newObject;
//	}
//	object->next = newObject;
//}
//
//void List::Index()
//{
//	object = GetInsertListAddress(objectVal);
//	while (object->next != nullptr)
//	{
//		object = object->next;
//		printf("%s\n", object->name);
//	}
//}
//
////void List::IndexReturn()
////{
////	while (object->prev != nullptr)
////	{
////		printf("%s\n", object->name);
////		object = object->prev;
////	}
////}
//
//Object* List::GetInsertListAddress(int val)
//{
//	for (int i = 0; i < val; i++)
//	{
//		if (headObject->next)
//		{
//			headObject = headObject->next;
//		}
//		else
//		{
//			break;
//		}
//	}
//	return headObject;
//}

void List::Create(const char* name,int objectVal)
{
	object = GetInsertListAddress(&headObject, objectVal);
}

Object* List::GetInsertListAddress(Object* object, int num)
{
	for (int i = 0; i < num; i++)
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
