#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#include "CSI.h"

using namespace std;
void Screen::clear()
{
	printf("\e[2J");
}
void Screen::render(int** buffer,int width,int height)
{
	for(int y=0;y<height;y++)
	{
		for(int x=0;x<width;x++)
		{
			int cell = *((int*)buffer + x*height + y);
			printBlock(cell);
		}
		printf("\n");
	}
}


Screen getScreen()
{
	Screen screen;
#ifdef TIOCGSIZE
	ttysize ts;
	ioctl(STDIN_FILENO,TIOCGSIZE,&ts);
	screen.width=ts.ts_cols;
	screen.height=ts.ts_lines;
#elif defined(TIOCGWINSZ)
 	winsize ts;
	ioctl(STDIN_FILENO,TIOCGWINSZ,&ts);
	screen.width=ts.ws_col;
	screen.height=ts.ws_row;
#endif
	return screen;
}

void resetColor()
{
	printf("\e[%d;%dm",F_DEFAULT,BG_DEFAULT);
}
void cursorUp(int n)
{
	printf("\e[%dA",n);
}
void cursorDown(int n)
{
	printf("\e[%dB",n);
}
void cursorForward(int n)
{
	printf("\e[%dC",n);
}
void cursorBack(int n)
{
	printf("\e[%dD",n);
}
void cursorNextLine(int n)
{
	printf("\e[%dE",n);
}
void cursorPreLine(int n)
{
	printf("\e[%dF",n);
}
void setCursorPos(int x,int y)
{
	printf("\e[%d;%dH",x,y);
}
void erase(int n)
{
    printf("\e[%dJ",n);
}
void eraseLine(int n)
{
    printf("\e[%dI",n);
}
void scrollUp(int n)
{
    printf("\e[%dS",n);
}
void scrollDown(int n)
{
    printf("\e[%dT",n);
}
void hideCursor()
{
    printf("\e[?25l");
}
void showCursor()
{
	printf("\e[?25h");
}

void printText(const int fColor, const int bgColor, const char* text)
{
	printf("\e[%d;%dm%s",fColor,bgColor,text);
	resetColor();
}
void printBlock(const int color)
{
	//char text[10];
	//sprintf(text,"%d",color);
	printText(F_DEFAULT,color," ");
}
void printRed(const char* text)
{
	printText(F_RED,BG_DEFAULT,text);
}
void printBlue(const char* text)
{
	printText(F_BLUE,BG_DEFAULT,text);
}
void printGreen(const char* text)
{
	printText(F_GREEN,BG_DEFAULT,text);
}
void printYellow(const char* text)
{
	printText(F_YELLOW,BG_DEFAULT,text);
}
void printMagenta(const char* text)
{
	printText(F_MAGENTA,BG_DEFAULT,text);
}
void printCyan(const char* text)
{
	printText(F_CYAN,BG_DEFAULT,text);
}
void printWhite(const char* text)
{
	printText(F_WHITE,BG_DEFAULT,text);
}
void printBlack(const char* text)
{
	printText(F_BLACK,BG_DEFAULT,text);
}
