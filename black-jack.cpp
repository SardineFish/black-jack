#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <memory.h>
#include <iostream>
#include <sstream>
#include <string>
#include "CSI.h"
using namespace std;
const int CARD_COUNT=52;
const int CARD_WIDTH=11;
const int CARD_HEIGHT=9;
const int CARD_INNER_WIDTH=9;
const int CARD_INNER_HEIGHT=7;
struct Poker
{
	string name;
	int value;
	int type;
	char graphic[CARD_INNER_HEIGHT][CARD_WIDTH + 16];
	void print(int x0,int y0);
};
void init();
void shuffle(Poker *rlist);
void readline(char* lnptr, int size, FILE *fp);
char getch();
Screen screen;
template <class T>
struct Node
{
	Node* next;
	T object;
};
Poker pokers[CARD_COUNT];
Poker *pokerShuffled;

int main()
{

	screen = getScreen();
	init();
	while(true)
	{
		if(pokerShuffled==NULL)
			pokerShuffled = (Poker*)malloc(sizeof(Poker)*CARD_COUNT);
		shuffle(pokerShuffled);
		for(int i=0;i<CARD_COUNT;i++)
		{
			printf("%d ",pokerShuffled[i].value);
		}
	}
	return 0;
}

void readline(char* lnptr, int size, FILE *fp)
{
	int idx=0;
	for(char ch=fgetc(fp);ch!='\n' && ch!=EOF; ch=fgetc(fp))
	{
		if(ch!='\r')	
			lnptr[idx++]=ch;
	}
}

void Poker::print(int x0,int y0)
{
	setCursorPos(x0, y0);
	printText(F_BLACK,BG_WHITE," --------- ");
	for(int y=0;y<CARD_INNER_HEIGHT;y++)
	{
		setCursorPos(x0,y0+y+1);
		printText(F_BLACK,BG_WHITE,"|");

		if(type==0 || type==1)
			printText(F_RED,BG_WHITE,graphic[y]);
		else
			printText(F_BLACK,BG_WHITE,graphic[y]);

		printText(F_BLACK,BG_WHITE,"|");
		//printf("\n");
	}
	setCursorPos(x0,y0+CARD_INNER_HEIGHT+1);
	printText(F_BLACK,BG_WHITE," --------- ");	
	printf("\n");
}
char getch()
{
	char ch;
	read(0,&ch,1);
	return ch;
}
void init()
{
	FILE *fin=fopen("poker.dat","r");
	int ln=1;
	int count=0;
	screen.clear();
	for(int i=0;i<CARD_COUNT;i++)
	{
		for(int y=0;y<CARD_INNER_HEIGHT;y++)
		{
			readline((pokers[i].graphic[y]), CARD_WIDTH, fin);
			//printf("%s\n",pokers[i].graphic[y]);
			//printText(F_BLACK,BG_WHITE,pokers[i].graphic[y]);
			//putchar('\n');
			//printRed(pokers[i].graphic[y]);
		}
		//cout << "\n";
		
		pokers[i].type=i/13;
		pokers[i].value=(i%13)+1;
		/*
		if((CARD_WIDTH+1)*(count+1)>screen.width)
		{
			ln+=CARD_HEIGHT+1;
			count=0;
		}
		pokers[i].print(count*(CARD_WIDTH+1)+1, ln);
		count++;
		printf("\n");*/
		printf("%d ",pokers[i].value);
	}

}
void shuffle(Poker *rlist)
{
	srand(time(NULL));
	int list[CARD_COUNT];

	for(int i=0;i<CARD_COUNT;i++)
	{
		list[i]=i;
	}
	for(int i=CARD_COUNT;i>0;i--)
	{
		int idx=rand()%i;
		int p=list[idx];
		for(int j=idx;j<i-1;j++)
		{
			list[j]=list[j]+1;
		}
		rlist[i-1].value=pokers[p].value;
		rlist[i-1].type=pokers[p].type;
		for(int y=0;y<CARD_INNER_HEIGHT;y++)
		{
			for(int x=0;x<CARD_WIDTH+16;x++)
			{
				rlist[i-1].graphic[y][x]=pokers[p].graphic[y][x];
			}
		}
	}
	/*
	for(int i=0;i<CARD_COUNT;i++)
	{
		rlist[i].print(1,i*2);
	}
	*/
}
