#include "Que2.h"

int main()
{
	int N, i, j=0, *indexes;
	pthread_t *tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
		
	char ch;
	scanf("%d", &N);
	
	D=(cno *)malloc(sizeof(cno)*N);
	temp=(cno *)malloc(sizeof(cno)*(N+1)/2);
	indexes=(int *)malloc(sizeof(int)*N);

	for(i=0;i<N;i++)
	{
		scanf("%d%c%c%d",&D[i].re,&ch,&ch,&D[i].im);
		indexes[i]=i;
	}
	printf("N=%d\n",N);
	for(i=0;i<N;i++)			//printing the complex numbers scanned
	{
		printf("CN%d %d+i%d\n",i,D[i].re,D[i].im);
	}

	if(N!=1)				//creates threads for complex multiplication if N>1
	{
		tid=(pthread_t *)malloc(sizeof(pthread_t)*(N/2));
		while(N!=1)	//continue until the number of elements for multiplication is exactly 1
		{	
			printf("\n");
			for(i=0;i<N/2;i++)	//creates (N/2) threads
			{
				pthread_create(&tid[i],&attr,runner,&indexes[i]);
				pthread_join(tid[i],NULL);
			}
			for(i=0;i<N/2;i++)	//prints output of (N/2) complex multiplications and copies the same to D[N]
			{
				printf("C%d%d %d+i%d\n",j,i,temp[i].re,temp[i].im);
				D[i] = temp[i];
			}
			j++;
			if(N%2==1)		//last odd input is transferred directly as output for the next processing
			{
				D[N/2]=D[N-1];
				printf("CN%d %d+i%d\n",N-1,D[N/2].re,D[N/2].im);
			}
			N=(N+1)/2;		//updates N value for next level thread generation
		}
		free(tid);	
	}
	
	free(D);
	free(temp);
	free(indexes);
	return 0;
}
