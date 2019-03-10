#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_sigusr1(int sig) 
{ 
    //printf("Caught signal %d\n", sig);
	printf("Le soldat numero %d, nous a quitté\n",getpid());
	exit(0); 
}

void handle_sigchld(int sig) 
{ 
    printf("Ton fils est mort Jonnhy\n");
}  

int main(int argc, char *argv[])
{
	int pipefd[2]; // 0 = lecture 1 = ecriture
	int pipefd2[2];
	int buf;
	int debit;
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
		printf("erreur");
		exit(-1);
	}
	else if(pid==0)
	{//fils
		//signal(10, handle_sigusr1);

		
		//while(1){}
	}
	else
	{//pere
		/*signal(10, handle_sigusr1);
		signal(SIGCHLD, handle_sigchld);*/
		//sleep(10);
		/*kill(pid, 10);
		while(1){}*/
	}		
	return 0;
}

