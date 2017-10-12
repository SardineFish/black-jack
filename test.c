#include<stdio.h>
int main()
{
	gets();
	printf("\e[10;10H");
	printf("233333333");
	printf("\e[11;10H");
	printf("23333333");
	return 0;
}
