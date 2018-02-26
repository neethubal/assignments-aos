#include "Que2.h"

void *runner(void *param)	//performs complex multiplication of D[2i] and D[2i+1] and stores in temp[i]
{
	int i=*((int *)param);
	temp[i].re=D[2*i].re*D[2*i+1].re-D[2*i].im*D[2*i+1].im;
	temp[i].im=D[2*i].re*D[2*i+1].im+D[2*i].im*D[2*i+1].re;
	pthread_exit((void *)0);
}

