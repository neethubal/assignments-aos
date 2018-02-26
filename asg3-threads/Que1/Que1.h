#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#define MAX_M 25	
#define MAX_PATHS 25

/* M 	   : Contains the number of elements in sequence array
   seq[]   : Stores the input sequence srray
   N	   : Contains the size of the Square Matrix
   matrix[][] : Stores the input square matrix */
int M, *seq, N, **matrix;

/* path[][]: Stores the paths found in forward order
   c[]     : Stores the count of each node in the sequence */
int **path,*c;

/* Input   : thread parameter which is an integer of the form <ijk> where <i,j> and <k> represents 
	     the position of element in matrix and sequence respectively
   Description: Thread function which returns success or failure for match of current element in 
	     the matrix and sequence. Calls runner2 which creates next level threads for finding 
	     valid path along right, below and diagonal directions */
extern void *runner1(void *param);

/* Input   : value = integer of the form <ijk> where <i,j> and <k> represents 
	     the position of element in matrix and sequence respectively
   Description: Creates next level threads for an element (represented by input value) for finding 
	     valid path along right, below and diagonal directions */
extern int runner2(int value);

/* Description: prints all the valid paths as stored in path[][] in reverse order */
extern void printpath();
