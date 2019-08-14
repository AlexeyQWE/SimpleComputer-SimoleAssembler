#pragma once

struct itimerval nval, oval;
unsigned int timer_control;

void signalhandler_Run(int signo);
void signalhandler_Reset(int signo);