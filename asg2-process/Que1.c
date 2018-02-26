#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/wait.h>
#define MAX_DEPTH 3
typedef struct Process
{
        int pid;
	int ppid;
	int depth;
	int cCount;
	struct Process *parent;
        struct Process *cnext;
        struct Process *cprev;
	struct Process *snext;
        struct Process *sprev;
}Process;

Process* insert(struct Process *Main, int pid, int ppid, int depth)
{
	Process *new, *temp, *temp1;		
	new=(Process *)malloc(sizeof(Process));
	new->pid=pid;
	new->ppid=ppid;
	new->depth=depth;
	new->cCount=0;
	new->parent=NULL;
	new->cnext=NULL;
	new->cprev=NULL;
	new->snext=NULL;
	new->sprev=NULL;
	
	int i=0,j=0,k=0,flag=0;
	if(Main==NULL)
    	{
		return new;
    	}
	else
	{
		temp=Main;
		while(temp!=NULL)
		{
			if(temp->pid!=ppid)		//child in depth > 1
			{
				i=0; j=1;
				while(flag==0)
				{
					if(i==0)
					{
						temp=Main; k=depth-j;
					}
					else
						k=depth-j-1;
					while(k>0)
					{
						temp=temp->cnext; k--;
					}
					i++; temp1=temp;
					if(i>1)
					{
						while(temp1->cnext!=NULL)
							temp1=temp1->cnext;
					}
					while(temp1->pid!=ppid)
					{
						temp1=temp1->snext;
						if(temp1->snext==temp->sprev||temp1==temp)
						{
							if(temp1->snext->pid==ppid)
								temp1=temp1->snext;
							break;
						}
					}
					if(temp1->pid==ppid)
						flag=1;
					else
					{
						if(temp->sprev==temp1->snext)
							j++;
						if(temp==temp1)
							k=0;
						else
							k=j;
						temp1=temp;
							while(k>0)
							{
								temp=temp->snext;
								k--;
							}
							temp=temp->snext;
						if(temp1->parent==temp)
							temp=temp->snext;
					}
				}
				temp=temp1;
			}
			if(temp!=NULL&&temp->pid!=ppid)
			{
				return Main;
			}
			if(temp->cCount==0)		//no child exists for temp
			{
				temp->cCount++;		//increment the child count of Main by 1
				temp->cnext=new;
				temp->cprev=new;
				new->parent=temp;
				new->snext=temp;
				new->sprev=temp;
				return Main;
			}
			else				//atleast one child exists for temp
			{
				temp->cCount++;	
				new->parent=temp;
				temp1=temp->cprev;
				temp->cprev=new;	//add new as last child of temp
				temp1->snext=new;
				new->sprev=temp1;
				new->snext=temp;
				return Main;
			}		
		}
	}
	return Main;
}

void inOrderTraversal(Process *Main)
{	
	Process *temp;
	int i,j=0;
	if(Main!=NULL)
	{
		if(Main->cnext!=Main->cprev)
		{
			if(Main->parent!=NULL&&Main->parent->cCount>2&&Main->parent->cnext!=Main)
				j=1;			
			else
				inOrderTraversal(Main->cnext);
		}
		if(Main->parent!=NULL&&Main->parent->cCount>2)
		{
			if(Main->parent->cnext==Main)
			{
				printf("%d\t",Main->pid);
			}
			else
			{
				i=Main->parent->cCount-2;
				temp=Main;
				while(i>0)
				{
					temp=temp->sprev;
					i--;
				}
				if(temp->cnext!=NULL)
				{
					inOrderTraversal(temp->cnext);
					printf("%d\t",temp->pid);
					inOrderTraversal(temp->cprev);
				}
				else
				{
					while(temp!=Main)
					{
						printf("%d\t",temp->pid);
						temp=temp->snext;
					}
				}
				if(j==1)
					printf("%d\t",Main->cnext->pid);
				printf("%d\t",Main->pid);
			}
		}
		else
			printf("%d\t",Main->pid);
		inOrderTraversal(Main->cprev);
	}	
}

int main (int argc,char *argv[])
{
	if(atoi(argv[2])>MAX_DEPTH)
	{
		printf("Enter a depth value < 4\n");
		exit(1);	
	}
	int i=0,j=0,k=0,l=0,level=1,n=1,status,flag=0;
	pid_t MainPID, pid, ppid, child[100];
	Process *Main;
	Main=NULL;
	
	FILE *fp;
	fp=fopen("output.txt","w");
	if(fp==NULL)
	{
		perror("fopen");
		exit(1);
	}
	k=atoi(argv[1]);
	MainPID=getpid();
	Main=insert(Main, MainPID, 0, 0);
		
	printf("\nStart of MAIN : PID=%d\n\n",MainPID);
	sleep(2);
	for(i=k;i>0;i--)
	{
		if(level<=atoi(argv[2]))
		{
			if(i!=1)
			{
				if(i==k)
					n=2*n-1;
				else
					n=n-1;
				if(level==1&&flag==0)		
				{	n=k; flag=1; }
			}
			else
			{
				if(n!=1)
					n=n-1;
			}			
			pid=fork();
			if(pid==0)		//child process
			{
				printf("PID=%d PPID=%d level=%d N=%d i=%d j=%d k=%d\n",getpid(),getppid(),level,n,i,j,k);
				fprintf(fp,"%d\t%d\t%d\t%d\t%d\t%d\t%d\n",getpid(),getppid(),level,n,i,j,k);
				kill(getpid(),SIGSTOP);
				signal(SIGSTOP,SIG_DFL);
				signal(SIGCONT,SIG_DFL);
				sleep(1);
				level++;	
				j=0;
				k=n;
				i=k+1;
			}
			else if(pid>0)		//parent process
			{
				sleep(1);
				child[j++]=pid;	//keeps track of PID's of CHILDREN; j at t: number of CHILDREN forked till time t
				if(i==1)	//continue the CHILDREN when PARENT has finished creating all CHILDREN in the level
				{
					sleep(1);
					for(l=0;l<j;l++)	//give SIGCONT to all CHILDREN
					{
						kill(child[l],SIGCONT);
					}
					for(l=0;l<j;l++)	//wait for all CHILDREN to finish
					{
						waitpid(child[l], &status,0);
						printf("Returned from PID %d PPID=%d status=%d\n",child[l],getpid(),status/256);
					}
				}
			}
			else			//fork error
			{
				perror("fork error");
				exit(0);
			}
			
		}
	}
	if(getpid()!=MainPID)
	{
		exit(n);
	}
	else
	{
		fclose(fp);
		system("sort -u output.txt|sort -k 2n -k 4rn > out.txt");	
		fp=fopen("out.txt","r");
		l=0;
		if(fp!=NULL)		//inserting to the process tree data structure
		{
			while(!(feof(fp)))
			{
				if(l!=0)		
				{
					fscanf(fp,"%d %d %d %d %d %d %d\n",&pid, &ppid, &level,&n,&i,&j,&k);
					Main=insert(Main, pid, ppid, level);
				}
				if(feof(fp))
					break;
				l++;
			} 
			fclose(fp);
		}
		printf("\nInorder Traversal of the Process Tree:\n");
		inOrderTraversal(Main); //traversing the process tree
		remove("output.txt");
		remove("out.txt");	
		printf("\n\nEnd of Main\n");	
	}
	return 0;
}
