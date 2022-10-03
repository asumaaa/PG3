#include <stdio.h>
#include <string.h>


//小さい方の数字を返す関数Min
template<typename Type>
Type Min(Type a, Type b)
{
	if (a <= b)
	{
		return static_cast<Type>(a);
	}
	return static_cast<Type>(b);
}

//char型の場合0を返す
template<>
char Min(char a,char b)
{
	return 0;
}

int main()
{
	printf("%d\n", Min<int>(1, 2));
	printf("%f\n", Min<float>(3, 4));
	printf("%lf\n", Min<double>(5, 6));
	if (Min('a', 'b') == 0)
	{
		printf("数字以外は入力できません\n");
	}

	return 0;
}