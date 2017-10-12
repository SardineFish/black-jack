#include "CSI.h"
namespace SardineFish {	
namespace CPP{
	const int ALN_LEFT=0;
	const int ALN_MID=1;
	const int ALN_RIGHT=2;
	class Graphics
	{
		public:
			Screen screen;
			inline int getPoint(int x,int y);
			inline void setPoint(int x,int y,int color);
			void clear();
			void clear(int color);
			void drawPoint(int x,int y,int color);
			void drawLine(int x1,int y1,int x2,int y2,int color,int lineWidth);
			void fillRect(int x,int y,int width,int height,int color);
			void strokeRect(int x,int y,int width,int height,int color,int lineWidth);
			void drawRect(int x,int y,int width,int height,int strokeColor,int lineWidth,int fillColor);
			void fillCircle(int x,int y,int r,int color);
			void strokeCircle(int x,int y,int r,int color,int lineWidth);
			void drawCircle(int x,int y,int r,int strokeColor,int lineWidth,int fillColor);
			void drawText(int x,int y,char* text);
			void drawText(int x,int y,char* text,int fColor,int bgColor);
			void drawText(int x,int y,char* text,int fColor,int bgColor,int align);
			void render();
			Graphics();
			~Graphics();
		private:
			int* buffer;
	};
}
}
