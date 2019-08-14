#include "SimpleComputer.h"

int main(int argc, char **argv) 
{
	keys key;

	int check = sc_memoryInit();
	int cycle = 0;

	if (check) {
		printf("sc_memoryInit Error\n\n");
		return -1;
	}
	sc_accInit();
	sc_InstrCounterInit();
	sc_regSet(REGFLAG_INTERRUPT, 1);
	printConsole();
	printFlags("Т", 15, 147);

    while (!cycle) {
    	mt_gotoXY(28, 33);
	    printf("Input/Output: \n");
	    rk_readkey(&key);
	    switch (key) 
	    {
	    	case KEY_r:	
	    		mh_push_r();
				break;

			case KEY_t:
				mh_push_t();
				break;

			case KEY_s:	
				mh_push_s();
				break;
			
			case KEY_l:
				mh_push_l();
				break;

			case KEY_i:
				mh_push_i();
				break;

			case KEY_f5:
				mh_push_F5();
				break;

			case KEY_f6:
				mh_push_F6();
				break;

			case KEY_up:
				mh_push_up();
				break;

			case KEY_down:
				mh_push_down();
				break;

			case KEY_left:
				mh_push_left();
				break;

			case KEY_right:
				mh_push_right();
				break;

			case KEY_q:
		 		 cycle = mh_push_q(cycle);
		 		break;
		}
	}
	return 0;
}

