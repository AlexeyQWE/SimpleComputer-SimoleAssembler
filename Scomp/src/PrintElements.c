#include "PrintElements.h"

int colomnsNames(void)
{
	mt_gotoXY(5, 79);
	printf("Memory");

	mt_gotoXY(5, 140);
	printf("accumulator");

	mt_gotoXY(8, 136);
	printf("instructionCounter");

	mt_gotoXY(11, 140);
	printf("Operation");

	mt_gotoXY(14, 140);
	printf("Flags");
	mt_gotoXY(15, 141);
	printf("П 0 М Т Е");

	mt_gotoXY(17, 112);
	printf("keys: \n");
	mt_gotoXY(18, 112);
	printf("l  - load\n");
	mt_gotoXY(19, 112);
	printf("s  - save\n");
	mt_gotoXY(20, 112);
	printf("r  - run\n");
	mt_gotoXY(21, 112);
	printf("t  - step\n");
	mt_gotoXY(22, 112);
	printf("i  - reset\n");
	mt_gotoXY(23, 112);
	printf("F5 - accumulator\n");
	mt_gotoXY(24, 112);
	printf("F6 - instructionCounter");
	mt_gotoXY(25, 112);
	printf("q - quit");
	
	return 0;
}

int setConsole(void)
{
	printAcc();
	bc_box(5, 35, 10, 91);

	for (int i = 0, height = 5; i < 4; ++i, height+=3) {
		bc_box(height, 128, 1, 32);
	}

	bc_box(17, 35, 8, 73);
	bc_box(17, 110, 8, 50);

	return 0;
}

int printConsole(void)
{ 
	mt_clrscr();
	setConsole();
	colomnsNames();
	printOperation();
	printMemory();
	carriage();
	printInstrCounter();
	printAcc();
	bc_setbigcharpos();
	print_terminal();
    return 0;
}

int carriage(void) 
{
	mt_gotoXY((int)(InstrCounter / 10) + 6, 9 * (InstrCounter - (int)(InstrCounter / 10) * 10) + 35 + 2);
	mt_setfgcolor(gray);
	mt_setbgcolor(green);

	if(MemoryArray[InstrCounter] >= 0)
		printf("+%.4x", MemoryArray[InstrCounter]);
	else
		printf("%.4x", MemoryArray[InstrCounter]);
	mt_setfgcolor(colorDefault);
	mt_setbgcolor(colorDefault);

	return 0;
}

int print_terminal(void)
{
	mt_gotoXY(29, 33);
	printf("WRITE: %.4x", terminal);
	return 0;
}

int printFlags(char *str, int X, int Y)
{
	mt_gotoXY(X, Y);
	mt_setfgcolor(green);
	mt_setbgcolor(gray);
	printf("%s", str);
	mt_setbgcolor(colorDefault);

	return 0;
} 

int printOperation(void)
{
	mt_gotoXY(12, 142);
	if (Operation >= 0)
		printf("+%.4x\n", Operation);
	else
		printf("%.4x\n", Operation);
	return 0;
}

int printInstrCounter(void)
{	
	mt_gotoXY(9, 142);
	if (InstrCounter >= 0)
		printf("+%.4d\n", InstrCounter);
	else
		printf("%.4d\n", InstrCounter);
	return 0;
}

int printAcc(void) 
{
	mt_gotoXY(6, 142);
	if (accumulator >= 0)
		printf("+%.4x",accumulator);
	else
		printf("%.4x",accumulator);
	return 0;
}

int printMemory() 
{
	int height = 6;
	mt_gotoXY(height, 37);
	for (int i = 0; i < MEMORYSIZE; ++i) {
		if ((i % 10 == 0) && i) {
			++height;
			mt_gotoXY(height, 37);
		}
		mt_setbgcolor(gray);
		mt_setfgcolor(black);

		if(MemoryArray[i] >= 0)
			printf("+%.4x", MemoryArray[i]);
		else
			printf("%.4x", MemoryArray[i]);
		mt_setbgcolor(colorDefault);
		printf("    ");
	}

	return 0;
}