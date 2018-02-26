#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#define MAX_N 100
#define MAX_INSTR 8	//max(instr in odd, instr in even)
#define DEF_PATH "/bin/echo"
int parsecmd(char *arg[], char cmd[])
{
	const char s[2] = " ";
   	int i=0;
   	arg[0] = strtok(cmd, s);		//get the first token 
   	while( arg[i] != NULL ) 		//walk through other tokens 
   	{
        	i++;
		arg[i]=strtok(NULL, s);
   	}
	arg[i-1][strlen(arg[i-1])-1]='\0';	//last character is read as '\n'; it is replaced with '\0'
	return i;
}
int main(int argc, char *argv[])
{
	int i,j=0,c;
	FILE *fp;
	pid_t pid[MAX_N];
	char cmd[2010], PATH[2010], *arg[2010];
	if(argc<2)
	{
		printf("Specify atleast one input file!\n");
		exit(0);
	}
	else
	{
		for(i=1;i<argc;i++)
		{
			pid[i]=fork();
			if(pid[i]==0)			//child process
			{
				fp = fopen(argv[i],"r");
				if(fp!=NULL)
				{
					while(!(feof(fp)))
					{
						fgets(cmd,2010,fp);
						c=parsecmd(arg,cmd);
						if(j==0&&strcmp(arg[0],"setpath")!=0)
						{
							strcpy(PATH,DEF_PATH);
						}
						j++;
						if(strcmp(arg[0],"setpath")==0)
						{
							strcpy(PATH,arg[1]);
							fgets(cmd,2010,fp);
							c=parsecmd(arg,cmd);
						}
						if(feof(fp))
							exit(3);
						sleep(2);
						kill(getpid(),SIGSTOP);
						signal(SIGSTOP,SIG_DFL);
						signal(SIGCONT,SIG_DFL);
						if(!fork())
						{
							if((execv(PATH,arg))<0)		
								perror("execv");		
						}
					} 
					fclose(fp);
				}
				else
				{
					perror("fopen");
					exit(2);
				}				
			}
			else if(pid[i]<0)		//fork error
			{
				perror("fork error");
				exit(1);
			}
			else
			{	
				; 			//do nothing for parent process
			}
		}
		for(i=0;i<MAX_INSTR;i++)		//loop for odd files
		{
			for(c=1;c<argc;c=c+2)
			{
				sleep(1); 
				if((kill(pid[c],SIGCONT)==-1))
					perror("sigcont");
			}
			sleep(1);
		}
		for(i=0;i<MAX_INSTR;i++)		//loop for even files
		{
			for(c=2;c<argc;c=c+2)
			{
				sleep(1);	
				if((kill(pid[c],SIGCONT)==-1))
					perror("sigcont");
			}
			sleep(1);
		}
	}
	return 0;
} 
