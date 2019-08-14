#pragma once
#include "SimpleComputer.h"

#define ACS_CKBOARD "█"
#define ACS_ULCORNER "l"
#define ACS_HLINE "q"
#define ACS_VLINE "x"
#define ACS_LLCORNER "m"
#define ACS_LRCORNER "j"
#define ACS_URCORNER "k"

int BIGCHAR_1[2] = {3233857728, 3233857728};
int BIGCHAR_2[2] = {3233857599, 4278389808};
int BIGCHAR_3[2] = {1019265852, 1019461824};
int BIGCHAR_4[2] = {4291019715, 3233857728};
int BIGCHAR_5[2] = {1057162239, 1019461824};
int BIGCHAR_9[2] = {3284386620, 1019461884};
int BIGCHAR_7[2] = {817938687, 202116144};
int BIGCHAR_8[2] = {1019462460, 1019462460};
int BIGCHAR_6[2] = {1057211196, 1019462595};
int BIGCHAR_0[2] = {3284386620, 1019462595};
int BIGCHAR_MINUS[2] = {0, 255};
int BIGCHAR_PLUS[2] = {404226048, 1579263};
int BIGCHAR_A[2] = {4241280252, 3435973836};
int BIGCHAR_B[2] = {2143535999, 2143536067};
int BIGCHAR_C[2] = {50578236, 1019413251};
int BIGCHAR_D[2] = {3284386623, 1069794243};
int BIGCHAR_E[2] = {4278387711, 4278387459};
int BIGCHAR_F[2] = {4278387711, 50529027};

int bc_printA(char *str);
int bc_box(int x1, int y1, int x2, int y2);
int bc_printbigchar(int *arr, int x, int y, enum Colors, enum Colors);
int bc_setbigcharpos();
int bc_getbigcharpos(int* big, int x, int y, int *value);
int bc_bigcharwrite(int fd, int* big, int count);
int bc_bigcharread(int fd, int*big, int need_count, int*count);
int *bc_InttoBC(int buff);