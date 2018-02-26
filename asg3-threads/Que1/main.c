#include "Que1.h"

int main()
{
	int i,j;
	
	path = (int **)malloc(MAX_PATHS*sizeof(int*));
	c = (int *)malloc(MAX_M*sizeof(int));

	scanf("%d", &M);				//Scanning the inputs		
	seq = (int *)malloc(M*sizeof(int));
	for(i=0;i<M;i++)
		scanf("%d",&seq[i]);

	scanf("%d",&N);
	matrix = (int **)malloc(sizeof(int *) * N);
	for(i=0;i<N;i++)
	{
		matrix[i]=(int *)malloc(sizeof(int) * N);
		for(j=0;j<N;j++)
			scanf("%d",&matrix[i][j]);
	}

	for(i=0;i<MAX_PATHS;i++)
	{
		c[i]=0;
		path[i]=(int *)malloc(M*sizeof(int));
	}

	
	printf("M\t\t:\t%d\n",M);			//Printing the sequence and the matrix elements	
	printf("Sequence Array  :\t");
	for(i=0;i<M;i++)			
		printf("%d ",seq[i]);
	printf("\nN\t\t:\t%d\nMatrix \t\t:\t",N);
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
			printf("%d ",matrix[i][j]);
		printf("\n");
		printf("\t\t\t");
	}

	if(matrix[0][0]!=seq[0])			//first element mismatch
	{
		printf("No Path\n");
		exit(0);
	}

	pthread_t tIdR, tIdB, tIdD;			//threads are created only if matrix[0][0]==seq[0]
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	int retR=0, retB=0, retD=0;
	
	int right=11, below=101, diag=111;		
	
	/*right, below, diag are integers of the form <ijk> where <i,j> and <k> represents the position of element in matrix and sequence respectively; this restricts the maximum value of M to be 10*/

	pthread_create(&tIdR,&attr,runner1,&right);
	pthread_create(&tIdB,&attr,runner1,&below);
	pthread_create(&tIdD,&attr,runner1,&diag);	
	pthread_join(tIdR,(void **)&retR);
	pthread_join(tIdB,(void **)&retB);
	pthread_join(tIdD,(void **)&retD);

	if(retR==0&&retD==0&&retB==0)	//if all threads returned failure
	{
		printf("\nNO PATH\n");
	}
	else
	{
		while(retR--)		//updates all the paths with <0,0> returning from <0,1>
		{
			path[c[0]][0] =0;
			c[0]++;
		}
		while(retB--)		//updates all the paths with <0,0> returning from <1,0>
		{
			path[c[0]][0] =0;
			c[0]++;
		}
		while(retD--)		//updates all the paths with <0,0> returning from <1,1>
		{
			path[c[0]][0] = 0;
			c[0]++;
		}	
		printf("\nNumber of Paths :\t%d\n",c[0]);		
		printpath();
	}
	
	free(seq);
	free(matrix);
	free(path);
	free(c);
	return 0;
}
