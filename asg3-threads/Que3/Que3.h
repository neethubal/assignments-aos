#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

/* N : contains the number of digits in the numbers to be multiplied */
int N;

/* A[], B[] : stores the input numbers to be multiplied by 1 digit per array location 
   pdt[] : stores the product of numbers stored in A[] and B[] */
int *A, *B, *pdt;

/* Input : Thread parameter which specifies the position (0,1,..(2N-1)-1) to get the sum of products
   Description : Thread returns the sum of products for position passed as thread parameter*/
extern void *runner(void *param);
