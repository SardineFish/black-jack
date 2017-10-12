#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include "CSI.h"
using namespace std;
const int CARD_COUNT=52;
const int CARD_WIDTH=11;
const int CARD_HEIGHT=7;
void init();
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
	char graphic[CARD_HEIGHT][CARD_WIDTH + 16];
	void print()
	{
		printText(F_BLACK,BG_WHITE," --------- ");
		printf("\n");
		for(int y=0;y<CARD_HEIGHT;y++)
		{
			printText(F_BLACK,BG_WHITE,"|");
			if(type==0 || type==1)
				printText(F_RED,BG_WHITE,graphic[y]);
			else
				printText(F_BLACK,BG_WHITE,graphic[y]);

			printText(F_BLACK,BG_WHITE,"|");
			printf("\n");
		}
		printText(F_BLACK,BG_WHITE," --------- ");
		printf("\n");
	}
};
Poker pokers[CARD_COUNT];
int main()
{
	init();
	return 0;
}
void init()
{
	FILE *fin=fopen("poker.dat","r");
	for(int i=0;i<CARD_COUNT;i++)
	{
		for(int y=0;y<CARD_HEIGHT;y++)
		{
			readline((pokers[i].graphic[y]), CARD_WIDTH, fin);
			//printf("%s\n",pokers[i].graphic[y]);
			//printText(F_BLACK,BG_WHITE,pokers[i].graphic[y]);
			//putchar('\n');
			//printRed(pokers[i].graphic[y]);
		}
		//cout << "\n";
		pokers[i].type=i/13;
		pokers[i].print();
		printf("\n");

	}
	printf("\n");
}
