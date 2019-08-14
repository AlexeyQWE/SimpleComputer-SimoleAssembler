#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include "myTerm.h"
#include "myBigChars.h"
#include "myReadkey.h"
#include "myHandler.h"
#include "CU.h"
#include "ALU.h"
#include "PrintElements.h"

#define MEMORYSIZE 100
#define COMMANDSIZE 13

#define REGFLAG_OVERFLOW 0
#define REGFLAG_ZERODIVISION 1
#define REGFLAG_OUTOFMEMORY 2
#define REGFLAG_INTERRUPT 3
#define REGFLAG_FALLSECOMMAND 4

struct termios orig_options;

int MemoryArray[MEMORYSIZE];
int regFlag;
int accumulator;
int InstrCounter;
int Operation;
int terminal;

int sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int* value);
int sc_memorySave(char* filename);
int sc_memoryLoad(char* filename);
int sc_regInit(void);
int sc_regSet(int reg,int value);
int sc_regGet(int reg, int* value);
int sc_commandEncode(int command, int operand, int* value);
int sc_commandDecode (int value, int * command, int * operand);
int funccmp(const void * x1, const void * x2);
int sc_InstrCounterInit(void);
int sc_accInit(void);
int sc_accSet(int address);
int sc_OperationInit(void);
int sc_InstrCounterSet(int address);
int sc_terminalInit(void);
int check_flags(void);
