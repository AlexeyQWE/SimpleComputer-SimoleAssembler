# include "myTerm.h"

int mt_clrscr(void)
{
	printf("\E[H\E[J");

	return 0;
}

int mt_gotoXY(int X, int Y) 
{
	int rows, cols;
	mt_getscreensize(&rows, &cols);

	if (X > rows || Y > cols || X < 0 || Y < 0)
		return -1;

	else
		printf("\E[%d;%dH", X, Y);

	return 0;
}

int mt_goCarraige(int X, int Y) 
{
	int rows, cols;
	mt_getscreensize(&rows, &cols);

	if (X > rows || Y > cols || X < 0 || Y < 0)
		return -1;

	else
		printf("\E[%d;%dH", Y, X);

	return 0;
}

int mt_getscreensize(int* rows, int* cols)
{
	struct winsize ws;
		if (!ioctl(1, TIOCGWINSZ, &ws)){
			*rows = ws.ws_row;
			*cols = ws.ws_col;
		} else {
			return -1;
		}
	return 0;
}

int mt_setfgcolor(Colors color)
{
	switch(color) 
	{
		case black:
		 	printf("\E[30m");
		 	break;
		 case red:
		 	printf("\E[31m");
		 	break;
		 case green:
		 	printf("\E[32m");
		 	break;
		 case yellow:
		 	printf("\E[33m");
		 	break;
		 case navyblue:
		 	printf("\E[34m");
		 	break;
		 case purple:
		 	printf("\E[35m");
		 	break;
		 case blue:
		 	printf("\E[36m");
		 	break;
		 case gray:
		 	printf("\E[37m");
		 	break;
		 case colorDefault:
		 	printf("\E[0m");
		 	break;
		 default:
		 	return -1;
	}
	return 0;
}

int mt_setbgcolor(Colors color)
{
	switch(color) 
	{
		case black:
		 	printf("\E[40m");
		 	break;
		 case red:
		 	printf("\E[41m");
		 	break;
		 case green:
		 	printf("\E[42m");
		 	break;
		 case yellow:
		 	printf("\E[43m");
		 	break;
		 case navyblue:
		 	printf("\E[44m");
		 	break;
		 case purple:
		 	printf("\E[45m");
		 	break;
		 case blue:
		 	printf("\E[46m");
		 	break;
		 case gray:
		 	printf("\E[47m");
		 	break;
		 case colorDefault:
		 	printf("\E[0m");
		 	break;
		 default:
		 	return -1;
	}
	return 0;	
}