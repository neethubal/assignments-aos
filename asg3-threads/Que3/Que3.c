#include "Que3.h"

void *runner(void *param)	//returns the sum of products for position passed as thread parameter
{
	int pos=*(int *)param,iA,iB,iB0,result=0;
	if(pos<N)
	{
		iA=pos;	iB=0;
	}
	else
	{
		iA=N-1;	iB=pos-N+1;
	}	
	iB0=iB;					
	while(iA>=iB0)   	
	{
		result += A[iA]*B[iB];   
		iA--;
		iB++;
	}	
	pthread_exit((void *)result);
}


