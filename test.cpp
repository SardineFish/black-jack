#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
using namespace std;
int main()
{
	while(true)
	{
		char ch;
		read(0,&ch,1);
		printf("%c",ch);
	}
	int *a,b[10]={1,2,3,4,5,6,7,8,9,0};
	a=b;
	srand(time(NULL));
	printf("%lf\n", (double)(clock()/CLOCKS_PER_SEC));
	return 0;
	for(int i=0;i<10;i++)
	{
		printf("%d ",rand()%52);
	}
	printf("%d",a[0]);
	printf("\e[10;10H");
	printf("233333333");
	printf("\e[11;10H");
	printf("23333333");
	return 0;
}
