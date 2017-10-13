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
void init();
void initAI();
void shuffle(int *rlist);
void readline(char* lnptr, int size, FILE *fp);
void printGame();
double Sum(double* arr, int from, int to);
long Sum(long* arr, int from, int to);
char waitInput();
double Prob(int point, int ex, int depth);
bool AIHit(Player* ai, Player* opp);
void deal(Player* player);
void dealerWin();
void playerWin();
void push();
void msleep(long milisec)
{
	usleep(milisec*1000);
}
//char getch();
Screen screen;
Poker pokers[CARD_COUNT];
Poker pokerBack;
int pokerShuffled[CARD_COUNT];
int pokerIdx;
double P[11];
int pokerCount[11];
Player player,dealer;
int main()
{
	/*
	initAI();
	while(true)
	{
		int point,ex;
		scanf("%d %d",&point, &ex);
		printf("Prob=%lf\n",Prob(point,ex,0));
	}
	*/
	screen = getScreen();
	init();
	char input='y';
	char text[1024];
	screen.clear();
	goto Start;
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
	scanf("%s",text);
	waitInput();
	if(text=="TD")
		exit(0);
	msleep(1000);
	printf("你没有选择的权力，开始吧！！！！\n\n");
	msleep(3000);
	Start:
	while(input=='y' || input=='Y' || input == '\n')
	{
		printf("洗牌...洗牌...洗牌\n");
		pokerIdx = 0;
		player.count=0;
		dealer.count=0;
		dealer.showCard=false;
		shuffle(pokerShuffled);
		printGame();
		msleep(800);
		deal(&dealer);
		printGame();
		msleep(800);
		deal(&dealer);
		printGame();
		msleep(800);
		deal(&player);
		printGame();
		msleep(800);
		deal(&player);
		printGame();
		do
		{
			printGame();
			printf("要牌么？(Y/n)");
			input = waitInput();
			if(input == 'Y' || input == 'y' || input == '\n')
			{
				deal(&player);
			}
			printGame();
			if(player.total()>21)
			{
				printf("\nBust!\n");
				dealerWin();
				goto EndGame;
			}

		}
		while (input == 'Y' || input == 'y' || input == '\n');
		dealer.showCard=true;
		printGame();
		printf("Calculating...\n");
		while (AIHit(&dealer, &player))
		{
			printGame();
			deal(&dealer);
			printGame();
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
		printf("\n要继续么？(Y/n)");
		input = waitInput();
	}
	return 0;
}
void initAI()
{
	
	for(int i=1;i<10;i++)
	{
		P[i]=1.0/13.0;
		pokerCount[i]=4;
	}
	pokerCount[10]=16;
	P[10]=4.0/13.0;
}
double Prob(int point, int ex, int depth)
{
	if(point > 21)
		return 0;
	if( (point == 21 || point>= ex))
		return 1;
	double prob = 0;
	for(int i=1;i<=10;i++)
	{
		if(pokerCount[i]<=0)
			continue;
		pokerCount[i]--;
		int sum = i + point;
		prob += P[i] * Prob(sum, ex, depth+1);
		pokerCount[i]++;
	}
	
	return prob;
}
bool AIHit(Player* ai, Player* opp)
{
	double n[22];
	double p[22];
	double winProb=0;
	for(int i=0;i<22;i++)
		n[i]=0;
	int oppP = opp->total() - pokers[opp->cards[0]].value;
	int aiP = ai->total();
	for(int i=1;i<=10;i++)
	{
		int sum = oppP+i;
		if(sum <= 21)
			n[sum] += P[i];
	}
	double sum = Sum(n, 1, 21);
	double ex=0;
	for(int i=1;i<22;i++)
	{
		p[i]=n[i]/sum;
		if(aiP >= i)
			winProb +=p [i];
		ex+=p[i]*i;
	}
	double prob = Prob(aiP,(int)ex, 0);
	if(prob > winProb+0.2)
		return true;
	else 
		return false;
}
void deal(Player* player)
{
	player->cards[player->count++]=pokerShuffled[pokerIdx++];
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
	return total;
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
	initAI();
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
	if(dealer.showCard)
		printf("共 %d 张手牌，总点数为：%d\n\n",dealer.count, dealer.total());
	else
		printf("共 %d 张手牌，总点数为：?\n\n",dealer.count);

	line += 3;
	for(int i=0;i<dealer.count;i++)
	{
		if(i==0 && !dealer.showCard)	
			pokerBack.print((CARD_WIDTH + 1) * i + 1, line);
		else
			pokers[dealer.cards[i]].print((CARD_WIDTH + 1) * i + 1, line);
	}
	line += CARD_HEIGHT + 2;
	setCursorPos(1,line);
	printf("这是你的手牌: \n");
	printf("共 %d 张手牌，总点数为：%d\n\n",player.count, player.total());
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
	printf("\n\n");
	printf("你输啦！！！哈哈哈哈哈哈！！！！\n\n");
	msleep(1000);
	printf("不再来一局何以挽回颜面？！\n\n");
}
void playerWin()
{
	printf("\n\n");
	printf("Emmmmmmmmm.........\n\n");
	msleep(1000);
	printf("这一定是Ai算法的锅....\n");
	msleep(800);
	printf("开发者刚刚优化了Ai算法，不再来一局？\n\n");
}
void push()
{
	printf("\n\n");
	printf("这表明……\n");
	msleep(800);
	printf("你的智商，和这辣鸡Ai算法，不相上下。\n\n");
	msleep(800);
	printf("不再来一局，以展示你身为人类的优越性？\n\n");
}
