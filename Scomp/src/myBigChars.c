#include "myBigChars.h"

int *bc_InttoBC(int buff) 
{
	switch (buff)
	{
		case 1:
			return BIGCHAR_1;
			break;
		case 2:
			return BIGCHAR_2;
			break;
		case 3:
			return BIGCHAR_3;
			break;
		case 4:
			return BIGCHAR_4;
			break;
		case 5:
			return BIGCHAR_5;
			break;
		case 6:
			return BIGCHAR_6;
			break;
		case 7:
			return BIGCHAR_7;
			break;
		case 8:
			return BIGCHAR_8;
			break;
		case 9:
			return BIGCHAR_9;
			break;
		case 10:
			return BIGCHAR_A;
			break;
		case 11:
			return BIGCHAR_B;
			break;
		case 12:
			return BIGCHAR_C;
			break;
		case 13:
			return BIGCHAR_D;
			break;
		case 14:
			return BIGCHAR_E;
			break;
		case 15:
			return BIGCHAR_F;
			break;
		case 0:
			return BIGCHAR_0;
			break;

		default:
			return NULL;
			break;
	}
}

int bc_printA(char *str) 
{
    printf("\E(0%s\E(B", str);
    return 0;
}

int bc_box(int x1, int y1, int x2, int y2)
{
	int temp = x1;

 	mt_gotoXY(x1, y1);
 	bc_printA(ACS_ULCORNER);

	for (int i = 0; i < y2; ++i) {
	
		bc_printA(ACS_HLINE);
	}

	bc_printA(ACS_URCORNER);

	for (int i = 0; i < x2; ++i) {
		mt_gotoXY(++x1, y1);
		bc_printA(ACS_VLINE);	
	}

	mt_gotoXY(++x1, y1);
	bc_printA(ACS_LLCORNER);
	
	for (int i = 0; i < y2; ++i) {
	
		bc_printA(ACS_HLINE);
	}

	x1 = temp;
	y1 +=y2 + 1;
	bc_printA(ACS_LRCORNER);
	mt_gotoXY(x1, y1);

	for (int i = 0; i < x2; ++i) {
		mt_gotoXY(++x1, y1);
		bc_printA(ACS_VLINE);	
	}


	return 0;
}

int bc_printbigchar(int ch[2], int x, int y, Colors fg, Colors bg) {
   mt_gotoXY(y, x);

  	mt_setfgcolor(fg);
	mt_setbgcolor(bg);

  	for(int i = 0; i < 2; ++i) {
    for(int j = 0, k = 0; j < 32; ++j, ++k) {
        (1 & (ch[i] >> j)) ? bc_printA(ACS_CKBOARD) : bc_printA(" ");
        if (k == 7 || k == 15 || k == 23 || k == 31)
            mt_gotoXY(y + (i*4 + k/10%10+1), x);
    	}
    }
    mt_setbgcolor(colorDefault);
    mt_gotoXY(32, 0);
    return 0;
}

int bc_setbigcharpos()
{
	if(MemoryArray[InstrCounter] >= 0)
		bc_printbigchar(BIGCHAR_PLUS, 2 + 46, 18, black, red);
	else
		bc_printbigchar(BIGCHAR_MINUS, 2 + 46, 18, black, red);

	for (int i = 0; i < 4; i++) {
		int digit = MemoryArray[InstrCounter] / pow(16, 3 - i);
		digit %= 16;
		digit = abs(digit);

		bc_printbigchar(bc_InttoBC(digit), i * 10 + 12 + 46, 18, black, red);
	}
	
	return 0;
}

int bc_getbigcharpos(int *arr, int x, int y, int *value)
{
	int pos;

	if ((x < 0) || (y < 0) || (x > 7) || (y > 7))
		return -1;
	if (y <= 3)
		pos = 0;
	else
		pos = 1;
	y = y % 4;
	*value = (arr[pos] >> (y*8 + x)) & 1;
	printf("value = %d\n", *value);

	return 0;
}

int bc_bigcharwrite(int fd, int *big, int count)
{
	int err;

	fd = open ("files/file1.txt", O_WRONLY);
	
	err = write(fd, &count, sizeof(count));
	if (err == -1)
		return -1;
	err = write(fd, big, count * (sizeof(int)) * 2);
	if (err == -1)
		return -1;
	
	return 0;
}

int bc_bigcharread(int fd, int *big, int need_count, int *count)
{
	int n, cnt, err;

	fd = open ("files/file.txt", O_RDONLY);
	
	err = read(fd, &n, sizeof(n));
	if (err == -1 || (err != sizeof(n)))
		return -1;
	cnt = read(fd, big, need_count * sizeof(int) * 2);
	if (cnt == -1)
		return -1;
	*count = cnt / (sizeof(int) * 2);
	
	return 0;
}
