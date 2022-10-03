#include <stdio.h>

//小さい方の数字を返す関数Min
template<typename Type>
Type Min(Type a, Type b)
{
	if (a <= b)return static_cast<Type>(a);
	return static_cast<Type>(b);
}

template<>
char Min<char>(char a,char b)
{
	return printf("数字は代入できません");
}

int main()
{
	printf("%d\n", Min<int>(1, 2));
	printf("%f\n", Min<float>(3, 4));
	printf("%lf\n", Min<double>(5, 6));
	printf("%c\n", Min<char>(7, 8));
	return 0;
}