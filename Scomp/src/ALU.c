#include "ALU.h"

int ALU(int command, int operand)
{
	switch (command) {
		case 0x30: 
			accumulator += MemoryArray[operand];
			break;
			
		case 0x31: 
			accumulator -= MemoryArray[operand];
			break;
		
		case 0x32: 
			if (MemoryArray[operand] != 0)
				accumulator /= MemoryArray[operand];
			else {
				sc_regSet(REGFLAG_ZERODIVISION, 1);
				return -1;
			}
			break;

		case 0x33: 
			accumulator *= MemoryArray[operand];
			break;
	}
	if ((accumulator > 0x7FFF)) 
		sc_regSet(REGFLAG_OVERFLOW, 1);
	
	return 0;
}