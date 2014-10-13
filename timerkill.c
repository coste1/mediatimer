//////////////////////////////////////////////////////////
/********************************************************/
/*							*/
/* mediatimer_beta.c					*/
/* Program to kill PROCESS after user defined period.	*/
/* Usage: ./mediatimer					*/
/*							*/
/* Future functionality to include multiple choice 	*/
/* PROCESS selection and use of hours, minutes and 	*/
/* seconds as opposed to just seconds input.		*/
/*							*/
/* TO DO:						*/
/* - Create and implement ASCII banner			*/
/* - Make timer display current countdown time on 	*/
/*   single line					*/
/* - Design and implement multiple choice menu		*/
/* - Implement PROCESS selection array for 1+ PROCESS	*/
/*							*/
/********************************************************/
//////////////////////////////////////////////////////////

#include <stdio.h> 	// library for input/output
#include <time.h> 	// library for CLOCKS_PER_SEC
#include <unistd.h>	// library for sleep() 
#include <stdlib.h> 	// library for exit() function

// function for the seconds tick
void wait( int sec )	// declare void function wait with argument int sec
{
	clock_t end_wait;	// set return type end_wait
	end_wait = clock() + sec * CLOCKS_PER_SEC;  // calculate time elapsed
	while (clock() < end_wait){}	// loop as long as processor time is less than end_wait
}

/* kpid function: kill process by name. 	*/
/* requires knowledge of PROCESS name.		*/
void kpid() {		// void function to remedy compile warning.

	FILE *p;	// assign pointer p

	p = popen("killall vlc", "r"); // kill process named vlc
	if(!p) {			// if process does not exist, error and exit.
		fprintf(stderr, "Error.");
		exit(1);
	}
	pclose(p);

}

/* run timer and print pid */
int main(void)
{
	int seconds, s;		// define variables
	time_t t;		// define function t
	struct tm *tm;		// ???

	tm = localtime(&t);	// find local time, assign address to t
	printf("Enter number of seconds: "); /* print expected input */
	scanf("%d", &seconds);	/* get input of seconds from user */
	s = seconds; /* store input seconds to variable s */

/* run timer */
	while(seconds > 0){

	tm->tm_sec = s;		// associates tm to tm_sec
	tm->tm_hour = s/3600;	// associates tm to tm_hour
	tm->tm_min = s/60;	// associates tm to tm_min

	mktime(tm);		// do?
/* print countdown, need to rectify issue with no disply using \r */
//	printf("%02d:%02d:%02d\r", tm->tm_hour, tm->tm_min, tm->tm_sec);
	s--;	/* decrement s by one */
	seconds--; /* decrement seconds by one */
	sleep(1); /* sleep process to ease CPU load */
	
	}
	kpid(); /* kill pid using function kpid */

	return 0;
}

