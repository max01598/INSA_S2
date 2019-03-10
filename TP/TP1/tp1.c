#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <math.h>


int main(int argc, char *argv[])
{
	int pipefd[2]; // 0 = lecture 1 = ecriture
	int pipefd2[2];
	float debit;
	if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
	if (pipe(pipefd2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }


	pid_t pid = 0;
	pid=fork();
	if (pid == -1){
		perror("fork error");
		exit(-1);
	}
	else if(pid==0)
	{//fils
		int i2 = 0;
		int buf =0;
		close(pipefd[1]);
		close(pipefd2[0]);//close le coté lecture
		while(i2 < 1000)
		{
			/* Lecture */;
			read(pipefd[0],&buf,sizeof(int));
			//printf("fils : %d\n",buf);
			
			/* Ecriture */
			i2 = buf +1 ;
			write(pipefd2[1],&i2, sizeof(int));
		}
		close(pipefd[0]);
		close(pipefd2[1]);
	}
	else
	{//pere
		clock_t clockdepart;
		clock_t clockfin;
		int i1 = 0;
		int buf2 = 0;
		close(pipefd[0]);//close le coté lecture
		close(pipefd2[1]);
		
		clockdepart = clock();
		while(buf2<1000)
		{			
			/* Ecriture */
			i1 = buf2 +1 ;
			write(pipefd[1],&i1, sizeof(int));

			/* Lecture */
			read(pipefd2[0],&buf2,sizeof(int));
			//printf("pere : %d\n",buf2);
		}
		close(pipefd[1]);
		close(pipefd2[0]);
		clockfin = clock();
		double duree = (double)(clockfin-clockdepart)/CLOCKS_PER_SEC;
		debit = (int)(1000*2*4*8)*pow(10,-6)/duree;
		printf("debit : %f Mega par seconde\n",debit);
	}
	
	return 0;
}

