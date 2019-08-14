#include "SimpleComputer.h"

int CommandArray[COMMANDSIZE] = {0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32, 0x33, 0x40, 0x41, 0x42, 0x43, 0x66};

int funccmp(const void * x1, const void * x2)
{
	 return ( *(int*)x1 - *(int*)x2 );  
}

int sc_memoryInit() 
{
	for (int i = 0; i < MEMORYSIZE; ++i) 
		MemoryArray[i] = 0;

	return 0;
}

int sc_memorySet(int address, int value)
{
	if (address >= MEMORYSIZE || address < 0) {
		return REGFLAG_OUTOFMEMORY;
	}
	MemoryArray[address] = value;
	return 0;
}

int sc_memoryGet(int address, int* value)
{
	if (address >= MEMORYSIZE || address < 0) {
		return REGFLAG_OUTOFMEMORY;
	}
	*value = MemoryArray[address];
	return 0;
}

int sc_memorySave(char* filename) 
{
	FILE *output = NULL;
	output = fopen(filename, "wb");

	if (!output)
		return -1;

	fwrite(MemoryArray, sizeof(*MemoryArray), MEMORYSIZE, output);
	fclose(output);

	return 0;
}

int sc_memoryLoad(char* filename) 
{
	FILE *input = NULL;
	input = fopen(filename, "rb");

	if (!input)
		return -1;

	for (int i = 0; i < MEMORYSIZE; ++i)
		fread(&MemoryArray[i], sizeof(*MemoryArray), MEMORYSIZE, input);
	fclose(input);

	return 0;
}

int sc_regInit(void) 
{
	regFlag = 0;
	return 0;
}

int sc_regSet(int reg, int value)
{
	if (reg < 0 || reg > 4)
		return -1;

	if (value != 1 && value != 0)
		return -1;	

	if (value == 1)
		regFlag = regFlag | (1 << reg);
	if (value == 0)
		regFlag = regFlag & (~(1 << reg));

	return 0;
}

int sc_regGet(int reg, int* value)
{
	if (reg < 0 || reg > 4)
		return -1;

	*value =  (regFlag >> reg) & 0x1;

	return 0;
}

int check_flags(void) 
{
	int tmp;
	sc_regGet(REGFLAG_INTERRUPT, &tmp);
	if (tmp == 1) 
		printFlags("Т", 15, 147);

	sc_regGet(REGFLAG_ZERODIVISION, &tmp);

	if (tmp == 1) 
		printFlags("0", 15, 143);

	sc_regGet(REGFLAG_OUTOFMEMORY, &tmp);

	if (tmp == 1) 
		printFlags("M", 15, 145);


	sc_regGet(REGFLAG_OVERFLOW, &tmp);
	if (tmp == 1) 
		printFlags("П", 15, 141);


	sc_regGet(REGFLAG_FALLSECOMMAND, &tmp);
	if (tmp == 1) 
		printFlags("Е", 15, 149);

	return 0;
}

int sc_accInit(void) 
{
	accumulator = 0;
	return 0;
}

int sc_accSet(int value) 
{
	accumulator = value;

	return 0;
}

int sc_InstrCounterInit(void) 
{
	InstrCounter = 0;
	return 0;
}

int sc_OperationInit(void)
{
	Operation = 0;
	return 0;	
}

int sc_InstrCounterSet(int address)
{
	InstrCounter = address;
	return 0;
}

int sc_terminalInit(void)
{
	terminal = 0;
	return 0;
}

int sc_commandEncode(int command, int operand, int* value)
{	
	void *ptr = (int*)bsearch(&command, CommandArray, COMMANDSIZE, sizeof(int), funccmp);

	if (ptr) {
		*value = (command << 7) | operand;
		return 0;
	}
	else
		return REGFLAG_FALLSECOMMAND;
}

int sc_commandDecode(int value, int * command, int * operand)
{
	void *true_command;
	int decoded_command, decoded_operand;
	int attribute;
	attribute = (value >> 14) & 1;
	
	if (!attribute) {
		decoded_command = (value >> 7) & 127;
		decoded_operand = value & 127;

		true_command = (int*)bsearch(&decoded_command, CommandArray, COMMANDSIZE, sizeof(int), funccmp);

		if (true_command != NULL) {
			*command = decoded_command;
			*operand = decoded_operand;
		}
		else {
			return REGFLAG_FALLSECOMMAND;
		}
	}
	return 0;
}
