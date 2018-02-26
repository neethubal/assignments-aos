#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>

/* structure for complex number */
typedef struct
{
	int re;			//real part
	int im;			//imagionary part
} cno;

/* D[] : array of cno structure to store the complex numbers
   temp[]: array of cno structure to store the temporary output calculated by thread function */
cno *D, *temp;	

/* Input: thread parameter which specifies the index i for the complex multiplication
   Description: performs complex multiplication of D[2i] and D[2i+1] and stores in temp[i] */
extern void *runner(void *param);

