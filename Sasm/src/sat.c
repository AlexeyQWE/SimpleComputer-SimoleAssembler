#include "sat.h"

int CommandArray[COMMANDSIZE] = {0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32, 0x33, 0x40, 0x41, 0x42, 0x43, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,0x68,
	0x69, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76};

int funccmp(const void * x1, const void * x2)
{
	 return ( *(int*)x1 - *(int*)x2 );  
}

int sc_commandEncode(int command, int operand, int* value)
{	
	void *ptr = (int*)bsearch(&command, CommandArray, COMMANDSIZE, sizeof(int), funccmp);

	if (ptr) {
		*value = (command << 7) | operand;
		return 0;
	}
	else
		return -1;
}

int str2sc_word(char *str, int *value)
{
	int pos = 0, plus = 1;
	int n;
	int byte1, byte2;

	if (str[0] == '+') {
		plus = 0;
		pos = 1;
	}
	if (sscanf(str + pos, "%x", &n) != 1)
		return -1;
	byte1 = n & 0xFF;
	byte2 = n >> 8;
	if ((byte1 > 0x7F) || (byte2 > 0x7F))
		return -1;
	*value = byte1 | (byte2 << 7) | (plus << 14);
	return 0;
}

int str2command(char *str)
{
	int ret;

	if (strcmp(str, "READ") == 0)
		ret = 0x10;
	else if (strcmp(str, "WRITE") == 0)
		ret = 0x11;
	else if (strcmp(str, "LOAD") == 0)
		ret = 0x20;
	else if (strcmp(str, "STORE") == 0)
		ret = 0x21;
	else if (strcmp(str, "ADD") == 0)
		ret = 0x30;
	else if (strcmp(str, "SUB") == 0)
		ret = 0x31;
	else if (strcmp(str, "DIVIDE") == 0)
		ret = 0x32;
	else if (strcmp(str, "MUL") == 0)
		ret = 0x33;
	else if (strcmp(str, "JUMP") == 0)
		ret = 0x40;
	else if (strcmp(str, "JNEG") == 0)
		ret = 0x41;
	else if (strcmp(str, "JZ") == 0)
		ret = 0x42;
	else if (strcmp(str, "HALT") == 0)
		ret = 0x43;
	else if (strcmp(str, "JNP") == 0)
		ret = 0x59;
	else if (strcmp(str, "NOT") == 0)
		ret = 0x51;
	else if (strcmp(str, "AND") == 0)
		ret = 0x52;
	else if (strcmp(str, "OR") == 0)
		ret = 0x53;
	else if (strcmp(str, "XOR") == 0)
		ret = 0x54;
	else if (strcmp(str, "JNS") == 0)
		ret = 0x55;
	else if (strcmp(str, "JC") == 0)
		ret = 0x56;
	else if (strcmp(str, "JNC") == 0)
		ret = 0x57;
	else if (strcmp(str, "JP") == 0)
		ret = 0x58;
	else if (strcmp(str, "JNP") == 0)
		ret = 0x59;
	else if (strcmp(str, "CHL") == 0)
		ret = 0x60;
	else if (strcmp(str, "SHR") == 0)
		ret = 0x61;
	else if (strcmp(str, "RCL") == 0)
		ret = 0x62;
	else if (strcmp(str, "RCR") == 0)
		ret = 0x63;
	else if (strcmp(str, "NEG") == 0)
		ret = 0x64;
	else if (strcmp(str, "ADDC") == 0)
		ret = 0x65;
	else if (strcmp(str, "SUBC") == 0)
		ret = 0x66;
	else if (strcmp(str, "LOGLC") == 0)
		ret = 0x67;
	else if (strcmp(str, "LOGRC") == 0)
		ret = 0x68;
	else if (strcmp(str, "RCCL") == 0)
		ret = 0x69;
	else if (strcmp(str, "RCCR") == 0)
		ret = 0x70;
	else if (strcmp(str, "MOVA") == 0)
		ret = 0x71;
	else if (strcmp(str, "MOVR") == 0)
		ret = 0x72;
	else if (strcmp(str, "MOVСA") == 0)
		ret = 0x73;
	else if (strcmp(str, "MOVСR") == 0)
		ret = 0x74;
	else if (strcmp(str, "ADDC") == 0)
		ret = 0x75;
	else if (strcmp(str, "SUBC") == 0)
		ret = 0x76;
	else
		ret = -1;
	
	return ret;
}

int pars_line(char *str, int *addr, int *value)
{
	char *ptr;
	int operand, command;
	int flag_assign = 0;
	
	ptr = strchr(str, ';');
	if (ptr != NULL)
		*ptr = '\0';
	ptr = strchr(str, '\n');
	if (ptr != NULL)
		*ptr = '\0';
	ptr = strtok(str, " \t");
	if (ptr == NULL)
		return EMPTY_STR;
	if (sscanf(ptr, "%d", addr) != 1) {
		return ERR_ARG1;
	}	
	if ((*addr < 0) || (*addr >= MEMORYSIZE))
		return ERR_ARG1;
	ptr = strtok(NULL, " \t");
	if (ptr == NULL)
		return ERR_FEW;
	else if (strcmp(ptr, "=") == 0)
		flag_assign = 1;
	else {
		command = str2command(ptr);
		if (command == -1)
			return ERR_ARG2;
	}
	ptr = strtok(NULL, " \t");
	if (ptr == NULL)
		return ERR_FEW;
	if (!flag_assign) {
		if (sscanf(ptr, "%d", &operand) != 1) {
			return ERR_ARG3;
		}
	}
	else {
		if (str2sc_word(ptr, value) == -1) {
			return ERR_ARG3;
		}
	}
	if ((operand < 0) || (operand >= MEMORYSIZE))
		return ERR_ARG3;
	ptr = strtok(NULL, " \t");
	if (ptr != NULL)
		return ERR_MANY;
	if (!flag_assign) {
		sc_commandEncode(command, operand, value);
	}
	return 0;
}

void print_error(char *line, int line_cnt, int err)
{
	switch (err) {
		case ERR_ARG1:
			fprintf(stderr, "%d: first argument isn't a number\n", line_cnt);
			break;
		
		case ERR_ARG2:
			fprintf(stderr, "%d: unknown command\n", line_cnt);
			break;
		
		case ERR_ARG3:
			fprintf(stderr, "%d: third argument isn't a number\n", line_cnt);
			break;
		
		case ERR_FEW:
			fprintf(stderr, "%d: should be three aguments\n", line_cnt);
			break;
		
		case ERR_MANY:
			fprintf(stderr, "%d: too many arguments\n", line_cnt);
			break;
	}
	fprintf(stderr, "%s", line);
}

int test_argv(char *argv[])
{
	char *ptr1, *ptr2;
	
	ptr1 = strrchr(argv[1], '.');
	ptr2 = strrchr(argv[2], '.');
	if ((strcmp(ptr1, ".sa") != 0) || (strcmp(ptr2, ".o") != 0))
		return -1;
	else
		return 0;
}

