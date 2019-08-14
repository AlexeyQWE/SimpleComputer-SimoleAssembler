#include "myHandler.h"
#include "timer.h"

int tmp;

void signalhandler_Run(int signo)
{
	CU();
	++InstrCounter;
	printConsole();
	check_flags();
	printf("\n");
}

void signalhandler_Reset(int signo)
{
	sc_memoryInit();
	sc_regInit();
	sc_accInit();
	sc_InstrCounterInit();	
	sc_OperationInit();
	sc_terminalInit();
	sc_regSet(REGFLAG_INTERRUPT, 1);
}

int mh_push_r() 
{
	keys key;
	
	if (tcgetattr(STDIN_FILENO, &orig_options))
		return -1;
	if (rk_mytermregime(0, 0, 0, 0, 0))
		return -1;

	mt_gotoXY(15, 147);
	printf("Т");

	sc_regInit();
	sc_regSet(REGFLAG_INTERRUPT, 0);

	signal (SIGALRM, signalhandler_Run);

	nval.it_interval.tv_sec = 1;
	nval.it_interval.tv_usec = 0;
	nval.it_value.tv_sec = 1;
	nval.it_value.tv_usec = 0;

	setitimer (ITIMER_REAL, &nval, &oval);

	while (1) {
		sc_regGet(REGFLAG_INTERRUPT, &tmp);
			if (tmp == 1) {
				alarm(0);
				break;
			}
		if (InstrCounter >= MEMORYSIZE - 1) {
			sc_regSet(REGFLAG_INTERRUPT, 1);
			check_flags();
			alarm(0);
			break;
		}
			rk_readkey(&key);
			if (key == KEY_i) {
					alarm(0);
					signal (SIGUSR1, signalhandler_Reset);
					raise (SIGUSR1);
					printConsole();
					check_flags();

					return 0;
			}
			signal (SIGALRM, signalhandler_Run);
		}
		if (tcsetattr(STDIN_FILENO, TCSANOW, &orig_options))
			return -1;

		return 0;
}

int mh_push_t()
{
	timer_control = 1;
	CU();
	printConsole();
	check_flags();
	timer_control = 0;
	return 0;
}

int mh_push_s()
{
	mt_gotoXY(30, 33);
	printf("Output file: ");
	fgets(fl[0], sizeof(*fl), stdin);
	sc_memoryLoad(fl[0]);
	printConsole();
	check_flags();
	return 0;
}

int mh_push_l()
{
	mt_gotoXY(30, 33);
	printf("Input file: ");
	fgets(fl[0], sizeof(*fl), stdin);
	sc_memorySave(fl[0]);
	printConsole();
	check_flags();
	return 0;
}

int mh_push_i()
{
	signal (SIGUSR1, signalhandler_Reset);
	raise (SIGUSR1);
	printConsole();
	check_flags();
	return 0;
}

int mh_push_F5()
{
	mt_gotoXY(30, 33);

	int value_of_cell;
	printf("Set value: ");
	scanf("%d", &value_of_cell);

	sc_accSet(value_of_cell);

	if ((accumulator > 0x7FFF)) 
		sc_regSet(REGFLAG_OVERFLOW, 1);

	printConsole();
	check_flags();

	return 0;
}

int mh_push_F6()
{
	mt_gotoXY(30, 33);

	int number_of_cell;
	printf("Go to cell: ");
	scanf("%d", &number_of_cell);

	if (number_of_cell < 0 || number_of_cell >= MEMORYSIZE) {
		sc_regSet(REGFLAG_OUTOFMEMORY, 1);
		printConsole();
		check_flags();
		return -1;
	}
	sc_InstrCounterSet(number_of_cell);	
	printConsole();
	check_flags();

	return 0;
}

int mh_push_up()
{
	if(InstrCounter / 10 > 0)
		InstrCounter -= 10;
	printConsole();
	check_flags();
	return 0;
}

int mh_push_down()
{
	if(InstrCounter / 10 < 9)
		InstrCounter += 10;
	printConsole();
	check_flags();
	return 0;
}

int mh_push_left()
{
	if(InstrCounter - (int)(InstrCounter / 10) * 10 > 0)
		--InstrCounter;
	printConsole();
	check_flags();
	return 0;
}

int mh_push_right()
{
	if(InstrCounter - (int)(InstrCounter / 10) * 10 < 9)
		++InstrCounter;
	printConsole();
	check_flags();
	return 0;	
}

int mh_push_q(int buff) 
{
	mt_gotoXY(32, 0);
	return (buff = 1);
}