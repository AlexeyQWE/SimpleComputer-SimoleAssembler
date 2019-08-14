#pragma once
#include "SimpleComputer.h"

typedef enum Colors
{
	black,
	red,
	green,
	yellow,
	navyblue,
	purple,
	blue,
	gray,
	colorDefault 

}Colors;

int mt_clrscr(void);
int mt_gotoXY(int X, int Y);
int mt_getscreensize(int* rows, int* cols);
int mt_setfgcolor(enum Colors);
int mt_setbgcolor(enum Colors);