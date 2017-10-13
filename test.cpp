#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
using namespace std;

int main()
{
	for(long i=0;i<1220703125;i++)
	{
		if(i%1000000==0)
			printf("%ld\n",i);
	}
	return 0;
	long N[22];
	double P[22];
	int V[14]={0,1,2,3,4,5,6,7,8,9,10,10,10,10};
	for(int i=0;i<22;i++)
	{
		N[i]=0;
		P[i]=0.00;
	}
	for(int i=1;i<=13;i++)
	{

	}
	for(int i=0;i<4;i++)
	{
		for(int x=1;x<=13;x++)
		{

		}
	}
	/*
	for(int a=1;a<=13;a++)
	{
		int sum;
		N[V[a]]++;
		for(int b=1;b<=13;b++)
		{
			sum = V[a] + V[b];
			if(sum>21)
				N[0]++;
			else
				N[sum]++;
			for(int c=1;c<=13;c++)
			{
				sum = V[a] + V[b] + V[c];
				if(sum>21)
					N[0]++;
				else
					N[sum]++;
				for(int d=1;d<=13;d++)
				{
					sum = V[a] + V[b] + V[c] + V[d];
					if(sum>21)
						N[0]++;
					else
						N[sum]++;

				}
			}
		}
	}
	*/
	long sum = 0;
	for(int i=1;i<22;i++)
	{
		sum += N[i];
		printf("%d ",N[i]);
	}
	printf("\n\n");
	for(int i=1;i<22;i++)
	{
		P[i]= (double)N[i] / (double)sum;
		printf("%lf ",P[i]);
	}
	printf("\n");
	return 0;
	
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
