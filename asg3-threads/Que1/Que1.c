#include "Que1.h"

void *runner1(void *param)
{
	//thread parameter is an integer of the form <ijk> where <i,j> and <k> represents the position of element in matrix and sequence respectively

	int value=*((int *)param), mat_i, mat_j, seq_i, count;
	mat_i=value/100;		//value is manipulated to obtain position of search element in matrix and sequence
	mat_j=(value/10)%10;
	seq_i=(value%10);
	
	if(matrix[mat_i][mat_j] != seq[seq_i])	//if current position in matrix and sequence are not matching
		pthread_exit((void *)0);

	count=runner2(value);			//proceeds for next level threads for right, below and diag for current position
	if(count)
		pthread_exit((void *)count);	//if path found, returns the count of paths where current element is part of
	else
		pthread_exit((void *)0);
}

int runner2(int value)
{
	pthread_t tIdR, tIdB, tIdD;
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	int retR=0, retB=0, retD=0, count=0;
	
	int mat_i, mat_j, seq_i;
	mat_i=value/100;
	mat_j=(value/10)%10;
	seq_i=(value%10);

	int right, below, diag;		
	//updates right, below and diag for next level matching
	right=(mat_i*100)+((mat_j+1)*10)+(seq_i+1);	//(Mi,Mj,Si)->(Mi,Mj+1,Si+1)
	below=((mat_i+1)*100)+(mat_j*10)+(seq_i+1);	//(Mi,Mj,Si)->(Mi+1,Mj,Si+1)
	diag=((mat_i+1)*100)+((mat_j+1)*10)+(seq_i+1);	//(Mi,Mj,Si)->(Mi+1,Mj+1,Si+1)


	if((mat_j+1)<N)					//for nodes except last in the row	
	{
		pthread_create(&tIdR,&attr,runner1,&right);
		pthread_join(tIdR , (void **)&retR);
		count += retR;
		while(retR--)
		{
			path[c[seq_i]][seq_i] = mat_i*10+mat_j;
			c[seq_i]++;
		}
	}
	
	if((mat_i+1)<N)					//for nodes except last in the column
	{
		pthread_create(&tIdB,&attr,runner1,&below);
		pthread_join(tIdB , (void **)&retB);
		count += retB;
		while(retB--)
		{
			path[c[seq_i]][seq_i] = mat_i*10+mat_j;
			c[seq_i]++;
		}
	}

	if(((mat_i+1)<N)&&((mat_j+1)<N))		//for nodes except last in both row and column
	{
		pthread_create(&tIdD,&attr,runner1,&diag);
		pthread_join(tIdD , (void **)&retD);
		count += retD;
		while(retD--)
		{
			path[c[seq_i]][seq_i] = mat_i*10+mat_j;
			c[seq_i]++;
		}
	}
	
	if(seq_i==M-1)  				//for the last node
	{
		path[c[seq_i]][seq_i] = mat_i*10+mat_j;
		c[seq_i]++;
		return 1;
	}
	return count;
}

void printpath()	//prints the paths in reverse order as stored in path[][]
{
	int i,j;
	printf("Paths\t\t:\t");
	for(j=0;j<c[0];j++)
	{
		for(i=M-1;i>=0;i--)
		{
			if(i==0)
				printf("(%d,%d)",path[j][i]/10,path[j][i]%10);
			else
				printf("(%d,%d)->",path[j][i]/10,path[j][i]%10);
		}
		printf("\n");
		printf("\t\t\t");
		
	}	
	printf("\n");
}
