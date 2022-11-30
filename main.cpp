#include <stdio.h> 
#include <stdlib.h>  
#include "vector"  
#include "list"
#include <iostream>
#include <windows.h> 
#include <algorithm> 
#include<fstream>
#include "sstream"

int main()
{
	std::stringstream studentsList;
	std::vector <std::string> students;

	//ファイルを開く
	std::ifstream file;
	file.open("student.csv");

	//ファイルの内容をコピー
	studentsList << file.rdbuf();

	//ファイルを閉じる
	file.close();

	//1行分の文字列を入れる変数
	std::string line;
	//生徒の名前と番号を代入
	while (getline(studentsList, line, ','))
	{
		//1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);
		std::string word;
		//カンマ区切りで先頭文字列を取得
		getline(line_stream, word);
		students.push_back(word);
	}

	std::sort(students.begin(), students.end());
	 

	//逐次実行
	for_each(std::begin(students), std::end(students), [](std::string str) {std::cout << str << std::endl; });

	system("pause");
	return 0;
}

