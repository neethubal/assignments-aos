#include "Que3.h"

int main()
{
	int i, j, k, c=0, num1, num2, *pos;
	int ret;
	pthread_t *tId;
	pthread_attr_t attr;
	
	scanf("%d %d",&num1,&num2);			//reads two numbers
	if( ((int)log10(num1)) != ((int)log10(num2)) )	
		printf("Enter numbers of equal length\n");
	else
	{
		N=(int)(log10(num1)+1);
		//printf("N=%d\n",N);
		
		A=(int *)malloc(N*sizeof(int)); 
		B=(int *)malloc(N*sizeof(int)); 		
		
		for(i=N-1;i>=0;i--)			//stores the numbers in integer arrays
		{
			A[i]=num1%10;	num1=num1/10;
			B[i]=num2%10;	num2=num2/10;
		}

		tId=(pthread_t *)malloc((2*N-1)*sizeof(pthread_t));
		pos=(int *)malloc((2*N-1)*sizeof(int));
		pdt=(int *)malloc((2*N)*sizeof(int));
		pthread_attr_init(&attr);
		for(i=0;i<=(2*N-1);i++)
			pdt[i]=0;
		for(i=0;i<(2*N-1);i++)		//2N-1 are created for getting the sum of products in pdt[]
		{
			pos[i]=i;
			pdt[2*N-2-i]=0;
			pthread_create(&tId[i],&attr,runner,pos+i);
			pthread_join(tId[i],(void **)&ret);
			pdt[2*N-2-i]=ret;
		}

		for(j=N;j>0;j--)
			printf("    ");
		for(i=0;i<N;i++)
			printf("%4d",A[i]);
		printf("  X\n");
		for(j=N;j>0;j--)
			printf("    ");
		for(i=0;i<N;i++)
			printf("%4d",B[i]);
		printf("\n-----------------------------------------------------------------------------------\n");	
		for(i=N-1,k=N;i>=0;i--,k--)	//prints the intermediate products for demonstration purpose	
		{
			for(j=k;j>0;j--)
				printf("    ");
			for(j=0;j<N;j++)
				printf("%4d",B[i]*A[j]);
			printf("\n");
		
		}
		printf("-----------------------------------------------------------------------------------\n");		
		printf("    ");
		for(i=2*N-2;i>=0;i--)		//prints the pdt[] computed from the 2N-1 threads
			printf("%4d",pdt[i]);
		for(i=0;i<(2*N-1);i++)		//performs the carry forwarding to get the final result
		{
			pdt[i]+=c;
			c=pdt[i]/10;
			pdt[i]%=10;
		}
		pdt[i]=c;		
		printf("\n-----------------------------------------------------------------------------------\n");
		for(i=2*N-1;i>=0;i--)
			printf("%4d",pdt[i]);
		printf("\n");
		free(A);
		free(B);
		free(pdt);
		free(pos);
		free(tId);
	}
	return 0;
}
