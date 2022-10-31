#include <stdio.h> 
#include <stdlib.h>  
#include "vector"  
#include "list"
#include <iostream>
#include <windows.h> 

int main()
{
	std::list<char> station;

	auto it = station.begin();

	it = "tokyo";

	std::cout << *it << std::endl;

	system("pause");

	return 0;
}