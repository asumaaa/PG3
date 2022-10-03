#include <stdio.h>


template<typename Type>
Type Min(Type a, Type b)
{
	if (a <= b)return static_cast<Type>(a);
	else if (a > b)return static_cast<Type>(b);
}

template<>
char Min<char>(char a,char b)
{
	return printf("”š‚Í‘ã“ü‚Å‚«‚Ü‚¹‚ñ\n");
}

int main()
{
	printf("%d\n", Min<int>(1, 2));
	printf("%f\n", Min<float>(3.0f, 4.0f));
	printf("%lf\n", Min<double>(5, 6));
	printf("%c\n", Min<char>(7, 8));
	return 0;
}