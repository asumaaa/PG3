#include <stdio.h>
#include <string.h>

template<typename Type1, typename Type2>
class Num
{
public: //メンバ変数
	Type1 a;
	Type2 b;
public: //メンバ関数
	//コンストラクタ
	Num(Type1 a, Type2 b) { Num::a = a; Num::b = b;};
	//小さい値を返す関数
	Type1 Min() { return (a < b) ? a : b; };
};

int main()
{
	//int<float
	Num<int, float> num1(2, 5);
	printf("%d\n", num1.Min());
	//int<double
	Num<int, float> num2(2, 5);
	printf("%d\n", num2.Min());
	//int>float
	Num<float, int> num3(2, 5);
	printf("%f\n", num3.Min());
	//int<double
	Num<double, int> num4(2, 5);
	printf("%lf\n", num4.Min());
	//float<double
	Num<float, double> num5(2, 5);
	printf("%f\n", num5.Min());
	//double<float
	Num<double, float> num6(2, 5);
	printf("%lf\n", num6.Min());

	return 0;
}
