#include <stdio.h>
#include <string.h>


//¬‚³‚¢•û‚Ì”š‚ğ•Ô‚·ŠÖ”Min
template<typename Type>
Type Min(Type a, Type b)
{
	if (a <= b)
	{
		return static_cast<Type>(a);
	}
	return static_cast<Type>(b);
}

//charŒ^‚Ìê‡0‚ğ•Ô‚·
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
		printf("”šˆÈŠO‚Í“ü—Í‚Å‚«‚Ü‚¹‚ñ\n");
	}

	return 0;
}