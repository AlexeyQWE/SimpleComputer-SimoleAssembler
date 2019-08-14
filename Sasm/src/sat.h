#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR_ARG1 -1
#define ERR_ARG2 -2
#define ERR_ARG3 -3
#define ERR_FEW -4
#define ERR_MANY -5
#define EMPTY_STR 1

#define MEMORYSIZE 100
#define COMMANDSIZE 38

int MemoryArray[MEMORYSIZE];

int str2sc_word(char *str, int *value);
int str2command(char *str);
int pars_line(char *str, int *addr, int *value);
void print_error(char *line, int line_cnt, int err);
int test_argv(char *argv[]);
int sc_commandEncode(int command, int operand, int* value);