#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>
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
void initAI();
void shuffle(int *rlist);
void readline(char* lnptr, int size, FILE *fp);
void printGame();
double Sum(double* arr, int from, int to);
long Sum(long* arr, int from, int to);
char waitInput();
bool AIHit();
void dealerWin();
void playerWin();
void push();
void msleep(long milisec)
{
	usleep(milisec*1000);
}
//char getch();
Screen screen;
template <class T>
struct Node
{
	Node* next;
	T object;
};
struct Player
{
	int cards[CARD_COUNT];
	int count=0;
	int money=0;
	bool showCard=false;
	int total();
};
Poker pokers[CARD_COUNT];
Poker pokerBack;
int pokerShuffled[CARD_COUNT];
int pokerIdx;
double P[11];
int pokerCount[11];
Player player,dealer;
int main()
{
	
	screen = getScreen();
	init();
	char input='y';
	screen.clear();
	setCursorPos(1,1);
	printf("*************************\n\n");
	printf("          好消息         \n\n");
	printf("*************************\n\n");
	printRed("好消息！\n\n");
	msleep(800);
	printGreen("好消息！\n\n");
	msleep(1200);
	printCyan("江南皮革厂倒闭了！\n\n");
	msleep(600);
	printCyan("          倒闭了！\n\n");
	msleep(600);
	printCyan("            闭了！\n\n");
	msleep(600);
	printCyan("              了！\n\n");
	msleep(800);
	printGreen("王八蛋老板【黄鹤】\n\n");
	msleep(800);
	printGreen("带着他的小姨子\n\n");
	msleep(1200);
	printRed("      *****************************\n");
	printRed("开设的     澳门首家首家线上赌场    上线啦！！！\n");
	printRed("      *****************************\n\n\n\n");
	msleep(3000);
	printf("欢迎来到   * 澳门首家线上赌场 *  \n\n");
	printf("是否开始游戏？(Y/n 回复TD退出游戏)");
	char text[1024];
	scanf("%s",text);
	waitInput();
	if(text=="TD")
		exit(0);
	msleep(1000);
	printf("你没有选择的权力，开始吧！！！！\n\n");
	msleep(3000);
	
	while(input=='y' || input=='Y')
	{
		printf("洗牌...洗牌...洗牌\n");
		pokerIdx = 0;
		/*
		if(pokerShuffled==NULL)
			pokerShuffled = (int*)malloc(sizeof(int)*CARD_COUNT);
		*/
		shuffle(pokerShuffled);
		do
		{
			printGame();
			printf("要牌么？(Y/n)");
			input = waitInput();
			if(input == 'Y' || input == 'y' || input == '\n')
				player.cards[player.count++]=pokerShuffled[pokerIdx++];
			if(player.total()>21)
			{
				printf("\nBust!\n");
				dealerWin();
				goto EndGame;
			}

		}
		while (input == 'Y' || input == 'y' || input == '\n');
		while (AIHit())
		{
			printGame();
			dealer.cards[dealer.count++] = pokerShuffled[pokerIdx++];

			if(dealer.total()>21)
			{
				printf("\nBust!\n");
				playerWin();
				goto EndGame;
			}
			msleep(1000);
		}
		if(player.total()>dealer.total())
			playerWin();
		else if (player.total()==dealer.total())
			push();
		else 
			dealerWin();
EndGame:

		input = waitInput();
	}
	return 0;
}
void initAI()
{
	for(int i=1;i<10;i++)
	{
		pokerCount[i]=4;
		P[i]=1.0/13.0;
	}
	P[10]=4.0/13.0;
}
double Prob(int point, double* p, int min)
{
	if(point == 21)
		return 1;
	if(point >21)
		return 0;
	double prob = 0;
	for(int i=1;i<=10;i++)
	{
		if(pokerCount[i]<=0)
			continue;
		pokerCount[i]--;
		int sum = i + point;
		if(sum < min)
		{
			prob += P[i] * Prob(sum, p, min);
		}
		for(int j = sum; j<=21; j++)
		{
			prob += P[i] * p[i];
		}
		pokerCount[i]++;
	}
	return prob;
}
bool AIHit()
{
	double n[22];
	double p[22];
	for(int i=0;i<22;i++)
		n[i]=0;
	int playerP = player.total() - pokers[player.cards[0]].value;
	for(int i=1;i<=10;i++)
	{
		int sum = playerP+i;
		if(sum <= 21)
			n[sum] += P[i];
	}
	double sum = Sum(n, 1, 21);
	for(int i=1;i<22;i++)
	{
		p[i]=n[i]/sum;
	}
	int dealerP = dealer.total();
	double prob = Prob(dealerP, p, playerP);
	if(prob > 0.5)
		return true;
	else 
		return false;
}
long Sum(long* arr, int from, int to)
{
	long sum=0;
	for(int i=from;i<=to;i++)
	{
		sum+=arr[i];
	}
	return sum;
}
double Sum(double* arr, int from, int to)
{
	double sum=0;
	for(int i=from;i<=to;i++)
	{
		sum+=arr[i];
	}
	return sum;
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
char waitInput()
{
	char input = 0;
	char ch = 0;
	while ((ch=getchar()) != '\n')
	{
		input = ch;
	}
	if (input == 0)
		input = ch;
	return input;
}
int Player::total()
{
	int total=0;
	for(int i=0;i<count;i++)
	{
		total += pokers[cards[i]].value;
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
/*
char getch()
{
	char ch;
	read(0,&ch,1);
	return ch;
}
*/
void init()
{
	FILE *fin=fopen("poker.dat","r");
	int ln=1;
	int count=0;
	//screen.clear();
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
		//printf("%d ",pokers[i].value);
	}
	for(int y=0;y<CARD_INNER_HEIGHT;y++)
	{
		readline(pokerBack.graphic[y], CARD_WIDTH, fin);
	}
	fclose(fin);
	//pokerBack.print(1,1);
}
void shuffle(int *rlist)
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
		rlist[i-1]=p;
		/*
		rlist[i-1].value=pokers[p].value;
		rlist[i-1].type=pokers[p].type;
		for(int y=0;y<CARD_INNER_HEIGHT;y++)
		{
			for(int x=0;x<CARD_WIDTH+16;x++)
			{
				rlist[i-1].graphic[y][x]=pokers[p].graphic[y][x];
			}
		}
		*/
	}
	/*
	for(int i=0;i<CARD_COUNT;i++)
	{
		rlist[i].print(1,i*2);
	}
	*/
}
void printGame()
{
	screen.clear();
	setCursorPos(1,1);
	int line=2;
	pokerBack.print(2,2);
	line+=CARD_HEIGHT+3;
	setCursorPos(1,line);
	printf("这是庄家的手牌: \n");
	int point=0;
	printf("共 %d 张手牌，总点数为：%d\n\n",dealer.count, point);
	line += 3;
	for(int i=0;i<dealer.count;i++)
	{
		pokers[dealer.cards[i]].print((CARD_WIDTH + 1) * i + 1, line);
	}
	line += CARD_HEIGHT + 2;
	setCursorPos(1,line);
	printf("这是你的手牌: \n");
	printf("共 %d 张手牌，总点数为：%d\n\n",player.count, point);
	line+=3;
	for(int i=0;i<player.count;i++)
	{
		pokers[player.cards[i]].print((CARD_WIDTH + 1) * i + 1, line);
	}
	line += CARD_HEIGHT + 2;
	setCursorPos(1,line);
}
void dealerWin()
{
}
void playerWin()
{
}
void push()
{
}
