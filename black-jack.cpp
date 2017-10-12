#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
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
void init();
void randomCard();
Screen screen;
void readline(char* lnprt, int size, FILE *fp)
{
	int idx=0;
	for(char ch=fgetc(fp);ch!='\n' && ch!=EOF; ch=fgetc(fp))
	{
		if(ch!='\r')	
			lnprt[idx++]=ch;
	}
}
struct Poker
{
	string name;
	int value;
	int type;
	char graphic[CARD_INNER_HEIGHT][CARD_WIDTH + 16];
	void print(int x0,int y0)
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
};
template <class T>
struct Node
{
	Node* next;
	T object;
};
Poker pokers[CARD_COUNT];
Poker *pokerList;
int main()
{
	screen = getScreen();
	init();
	randomCard();
	return 0;
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
		/*
		if((CARD_WIDTH+1)*(count+1)>screen.width)
		{
			ln+=CARD_HEIGHT+1;
			count=0;
		}
		pokers[i].print(count*(CARD_WIDTH+1)+1, ln);
		count++;
		printf("\n");*/
	}
}
void randomCard()
{
	srand(time(NULL));
	Node<Poker> *list=new Node<Poker>();
	Node<Poker> *p=list;
	for(int i=0;i<CARD_COUNT;i++)
	{
		p->object=pokers[i];
		p->next=new Node<Poker>();
		p=p->next;
	}
	Poker rlist[CARD_COUNT];
	for(int i=CARD_COUNT;i>0;i--)
	{
		int idx=rand()%i;
		p=list;
		for(int j=0;j<idx;j++)
		{
			p=p->next;
		}
		rlist[i-1]=p->next->object;
		p->next=p->next->next;
	}
	for(int i=0;i<CARD_COUNT;i++)
	{
		rlist[i].print(1,i*2);
	}
}
