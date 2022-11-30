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
	std::vector <int> num1;
	std::vector <int> num2;

	//各クラスの人数
	int AClassVol = 24;
	int BClassVol = 30;
	int CClassVol = 25;
	int DClassVol = 17;

	//ファイルを開く
	std::ifstream file;
	file.open("student.csv");

	//ファイルの内容をコピー
	studentsList << file.rdbuf();

	//ファイルを閉じる
	file.close();

	//1行分の文字列を入れる変数
	std::string line;
	int num = 1;
	//生徒の名前と番号を代入
	while (getline(studentsList, line, ','))
	{
		//1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);
		std::string word;
		//カンマ区切りで先頭文字列を取得
		getline(line_stream, word);
		students.push_back(word);
		num1.push_back(num);
		num++;
	}

	//名前によって番号代入
	for (int i = 0; i < students.size(); i++)
	{
		std::string str1 = students[i].substr(0, 4);
		std::string str2 = students[i].substr(5, 2);
		if (str1 == "LE2A") {
			num2.push_back(atoi(str2.c_str()));
		}
		if (str1 == "LE2B") {
			num2.push_back(AClassVol + atoi(str2.c_str()));
		}
		if (str1 == "LE2C") {
			num2.push_back(AClassVol + BClassVol + atoi(str2.c_str()));
		}
		if (str1 == "LE2D") {
			num2.push_back(AClassVol + BClassVol + CClassVol + atoi(str2.c_str()));
		}
	}

	/*std::vector<std::string> str = students;
	for (int i = 0; i < students.size(); i++)
	{
		for (int j = 0; j < students.size(); j++)
		{
			if (num1[i] == num2[j])
			{
				std::replace(students.begin(), students.end(), str[i], students[j]);
			}
		}
	}*/
	std::sort(students.begin(), students.end());


	//逐次実行
	for_each(std::begin(students), std::end(students), [](std::string str) {std::cout << str << std::endl; });

	/*for (int i = 0; i < students.size(); i++)
	{
		std::cout << students[i] << std::endl;
	}*/

	/*for (int i = 0; i < num1.size(); i++)
	{
		std::cout << num1[i] << std::endl;
	}

	printf("\n");

	for (int i = 0; i < num2.size(); i++)
	{
		std::cout << num2[i] << std::endl;
	}*/

	////各クラスの人数
	//int AClassVol = 24;
	//int BClassVol = 30;
	//int CClassVol = 25;
	//int DClassVol = 17;

	//std::string str;
	//int num;
	//for (int i = 0; i < studentsList.size(); i++)
	//{
	//	//クラス名を取得
	//	str = studentsList[i].substr(0.4);
	//	if (str == "LE2A")num = AClassVol;
	//	if (str == "LE2B")num = BClassVol;
	//	if (str == "LE2C")num = CClassVol;
	//	if (str == "LE2D")num = DClassVol;

	//	//出席番号を取得
	//	str = studentsList[i].substr(5.2);
	//	num += atoi(str.c_str());

	//	//置き換え
	//	std::replace(students)
	//}
	

	system("pause");
	return 0;
}

