#include "CU.h"
#include "timer.h"

void CU()
{
	int command, operand;
	
	if (InstrCounter >= MEMORYSIZE) {
		sc_regSet(REGFLAG_OUTOFMEMORY, 1);
		sc_regSet(REGFLAG_INTERRUPT, 1);
		return;
	}
	if (sc_commandDecode(MemoryArray[InstrCounter], &command, &operand) != 0) {
		sc_regSet(REGFLAG_FALLSECOMMAND, 1);
		sc_regSet(REGFLAG_INTERRUPT, 1);
		return;
	}
	Operation = command;

	if ((operand < 0) && (operand >= MEMORYSIZE)) {
		sc_regSet(REGFLAG_FALLSECOMMAND, 1);
		sc_regSet(REGFLAG_INTERRUPT, 1);
		return;
	}
	if ((command >= 0x30) && (command <= 0x33)) {
		if (ALU(command, operand) != 0) {
			sc_regSet(REGFLAG_INTERRUPT, 1);
			return;
		}
	}
	else {
		switch(command)
		{
			case 0x10:
				if(intput_cell(operand) == -1)
					sc_regSet(REGFLAG_OVERFLOW, 1);
				break;

			case 0x11:
				sc_memoryGet(operand, &terminal);
				break;

			case 0x20: 
				accumulator = MemoryArray[operand];
				break;
			
			case 0x21: 
				MemoryArray[operand] = accumulator;
				break;
			case 0x40:
				InstrCounter = operand;
				break;
			case 0x41:
				if (accumulator < 0)
					InstrCounter = operand;
				break;
			case 0x42:
				if (accumulator == 0)
					InstrCounter = operand;
				break;
			case 0x43: 
				sc_regSet(REGFLAG_INTERRUPT, 1);
				break;
			case 0x66:
				if (accumulator < 0 || accumulator >= MEMORYSIZE) 
					sc_regSet(REGFLAG_OUTOFMEMORY, 1);
				else 
					accumulator = MemoryArray[operand] - MemoryArray[accumulator];
				break;
		}
	}
	if ((accumulator > 0x7FFF)) 
		sc_regSet(REGFLAG_OVERFLOW, 1);
}

int intput_cell(int operand)
{
	if (!timer_control) {
		alarm(0);
		if (rk_mytermregime(1, 1, 1, 1, 1))
		return -1;
	}

	mt_gotoXY(30, 33);
	int cell;
	printf("READ: ");
	scanf("%x", &cell);
	sc_memorySet(operand, cell);

	if (!timer_control) {
		nval.it_interval.tv_sec = 1;
		nval.it_interval.tv_usec = 0;
		nval.it_value.tv_sec = 1;
		nval.it_value.tv_usec = 0;
		setitimer (ITIMER_REAL, &nval, &oval);
		signal (SIGUSR1, signalhandler_Run);
	}

	if (MemoryArray[operand] > 0x7FFF)
		return -1;
	return 0;
}
