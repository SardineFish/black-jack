#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Graphics.h"
namespace SardineFish
{
namespace CPP
{
	inline int sign(const int x)
	{
		if(x<0)
			return -1;
		else if(x==0)
			return 0;
		else
			return 1;
	}
	inline int Graphics::getPoint(int x,int y)
	{
		return buffer[y*screen.width+x];
	}
	inline void Graphics::setPoint(int x,int y,int color)
	{
		buffer[y*screen.width + x]=color;
	}
	void Graphics::clear()
	{
		fillRect(0,0,screen.width,screen.height,BG_BLACK);
	}

	void Graphics::clear(int color)
	{
		fillRect(0,0,screen.width,screen.height,color);
	}

	void Graphics::drawPoint(int x,int y,int color)
	{
		setPoint(x,y,color);
	}
	void Graphics::drawLine(int x1,int y1,int x2,int y2,int color,int lineWidth)
	{
		int step=sign(x2-x1);
		double k=(y2-y1)/(x2-x1);
		for(int x=x1;x<=x2;x++)
		{
			int y=k*(x-x1)+y1;
			setPoint(x,y,color);
		}
	}
	void Graphics::fillRect(int x0,int y0,int width,int height,int color)
	{
		for(int y= y0<0 ? 0 : y0; y<y0+height && y<screen.height; y++)
		{
			for(int x= x0<0 ? 0 : x0; x<x0+width && x<screen.width ;x++)
			{
				setPoint(x,y,color);
			}
		}
	}
	void Graphics::strokeRect(int x,int y,int width,int height,int color,int lineWidth)
	{
	}
	void Graphics::drawRect(int x,int y,int width,int height,int strokeColor,int lineWidth,int fillColor)
	{
	}
	void Graphics::fillCircle(int x,int y,int r,int color)
	{
	}
	void Graphics::strokeCircle(int x,int y,int r,int color,int lineWidth)
	{
	}
	void Graphics::drawCircle(int x,int y,int r,int strokeColor,int lineWidth,int fillColor)
	{

	}
	void Graphics::drawText(int x,int y,char* text)
	{
		drawText(x,y,text,F_DEFAULT,BG_DEFAULT,ALN_LEFT);
	}
	void Graphics::drawText(int x,int y,char* text,int fColor,int bgColor)
	{
		drawText(x,y,text,fColor,bgColor,ALN_LEFT);
	}
	void Graphics::drawText(int x,int y,char* text,int fColor,int bgColor,int align)
	{
		
	}
	void Graphics::render()
	{
		erase(ED_BEGIN);
		cursorBack(screen.width*2);
		cursorUp(screen.height);
		hideCursor();
		int err=0;
		for(int y=0;y<screen.height;y++)
		{
			if(y!=0)
				printf("\n");
			for(int x=0;x<screen.width;x++)
			{
				int p=buffer[y*screen.width+x];
				printBlock(p);
				printBlock(p);
			}
		}
		cursorUp(screen.height);
		cursorBack(screen.width*2);
		
	}
	Graphics::Graphics()
	{
		screen=getScreen();
		screen.width/=2;
		buffer=new int[screen.width*screen.height];
		//int b[screen.width][screen.height];
		for(int y=0;y<screen.height;y++)
		{
			for(int x=0;x<screen.width;x++)
			{
				buffer[y*screen.width+x]=BG_BLACK;
			}
		}
		hideCursor();
	}
	Graphics::~Graphics()
	{
		showCursor();
	}

}
}
