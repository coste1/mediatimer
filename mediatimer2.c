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

/* start include block */
#include <stdio.h> 	// library for input/output
#include <time.h> 	// library for CLOCKS_PER_SEC
#include <unistd.h>	// library for sleep() 
#include <stdlib.h> 	// library for exit() function
/* end include block */

/* start define block */
#define MT_VER_MAJOR 0
#define MT_VER_MINOR 1
#define MT_VER_PATCH 0
#define MT_AUTHOR "Thomas Jost <tjost@makeshiftmammoth.com>"
#define C_ONE "mpd"
#define C_TWO "vlc"
#define C_THREE "hexchat"
#define C_FOUR "utorrent"
#define C_FIVE "irssi"
#define C_SIX "Other"
#define ARRAY_SIZE 80
/* end define block */

// Time variables struct
typedef struct
{
	int hours;
	int minutes;
	int seconds;
} Time;

// time-to-seconds conversion
static inline int time_to_sec(Time t)
{
	return (t.hours * 60 + t.minutes) * 60 + t.seconds;
}

// seconds-to-time conversion
static inline Time sec_to_time(int s)
{
	Time t;
	t.hours = s / 3600;
	t.minutes = (s / 60) % 60;
	t.seconds = s % 60;
	return t;
}

// get time from user
static int get_time(char const *prompt, Time *t)
{
	int rc = -1; // assume failure
	if (scanf("%d:%d:%d", &t->hours, &t->minutes, &t->seconds)!= 3)
		fprintf(stderr, "Failure to receive time in format hh:mm:ss\n");
	else if(t->seconds < 0 || t->seconds > 59)
		fprintf(stderr, "Seconds value is not in range 0..59\n", t->seconds);
	else if(t->minutes < 0 || t->minutes > 59)
		fprintf(stderr, "Minutes value is not in range 0..59\n", t->minutes);
	else if(t->hours < 0 || t->hours > 24)
		fprintf(stderr, "Hours value is not in range 0..24\n", t->hours);
	else if(t->hours == 24 && (t->seconds != 0 || t->minutes != 0))
		fprintf(stderr, "Maximum time value is 24:00:00 (you gave %2d:%.2d:%.2d)\n",
			t->hours, t->minutes, t->seconds);
	else
		rc=0; // All ok
	return rc;
}

/* kpid function: kill process by name. 	*/
/* requires knowledge of PROCESS name.		*/
void kpid(char * name) {		// void function to remedy compile warning.

	FILE *p;	// assign pointer p
	char command[ARRAY_SIZE];;
//	int len;
	

//	len = snprintf(command, sizeof(command), "killall",a);
//	if(len <=sizeof(command))
//	{
		p = popen(command,"r");
	if(!p) {			// if process does not exist, error and exit.
		fprintf(stderr, "Error.");
		exit(1);
	}
	pclose(p);
}

/* print usage menu */
/* this is most likely incorrect, but we'll use it for */
/* the time being. need functioning code to present to */
/* others for better direction and understanding.      */
static void usage() {
  printf("mediatimer v. %d.%d.%dalpha by %s\n",
	MT_VER_MAJOR,MT_VER_MINOR,MT_VER_PATCH,MT_AUTHOR);
  printf(
    "Usage: ./mediatimer2\n"
    "===========================================================\n"
    "|	-h		-	Print this		  |\n"
    "===========================================================\n"
    "Available options are:				\n"
    "	1) %s		3) %s		5) %s		\n"
    "	2) %s		4) %s		6) %s		\n",
    C_ONE,C_THREE,C_FIVE,C_TWO,C_FOUR,C_SIX);
}

int main(void)
{
	Time t;
	char index, process[ARRAY_SIZE];


	printf("Enter time until kill: "); /* print expected input */
	if (get_time("Time entered: ", &t) != 0)
		exit(1);

	printf("Enter process name: "); /* print expected input */
	scanf("%79s", process); // take input, load into array
	/* opt for the next code segment instead of scanf if possible */
	//fgets(process,sizeof(process),stdin);
	process[strlen(process)-1] = '\0';

	for(index = 0; index < ARRAY_SIZE; index++) {
		process[index] = 0;
		printf("process[%d] = %s\n", index, process[index]);
	}

	int sec = time_to_sec(t);

/* run timer */
	while(sec > 0)
	{
		/* print countdown, need to rectify issue with no disply using \r */
		printf("%2d:%.2d:%.2d\r", t.hours, t.minutes, t.seconds);
		sec--; /* decrement seconds by one */
		sleep(1); /* sleep process to ease CPU load */
	}
	// kpid(process); /* kill pid using function kpid */

	return 0;
}

