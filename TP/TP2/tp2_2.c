#include <stdio.h> 
#include <pthread.h> 
#include <sys/sem.h> 
#include <unistd.h> 


int main()
{
	int pid = 0;
	pid=fork();
	if(pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
	{//fils processus P2
		key_t key = 23;//identifie le semaphore pour le partage 
		int semaphore;
		char buf[10];
		semaphore = semget(key,1,0666|IPC_CREAT);
		union semum sem;//arg de semctl
		sem.val = 1;
		semctl(semaphore,0,SETVAL,sem)//initilise la valeur initiale du sémaphore SETVAL + initialisation
		struct sembuf;//structure pour operation p ou v
		sembuf.sem_num = 0;
		sembuf.sem_op = -1;//donne p
		sembuf.sem_flag = 0;
		while(1)
		{
			semop(semaphore,&buf,1)//instruct 1 = nombre de structure
			printf("Second Process : (write something)");
			scanf("%s", buf);
			sembuf.sem_op = 1;//donne v
		}
	}
	else
	{//processus P1
		key_t key = 23;//identifie le semaphore pour le partage 
		int semaphore;
		char buf[10];
		semaphore = semget(key,1,0666|IPC_CREAT);
		union semum sem;//arg de semctl
		sem.val = 1;
		semctl(semaphore,0,SETVAL,sem)//initilise la valeur initiale du sémaphore SETVAL + initialisation
		struct sembuf;//structure pour operation p ou v
		sembuf.sem_num = 0;
		sembuf.sem_op = -1;//donne p
		sembuf.sem_flag = 0;
		while(1)
		{
			semop(semaphore,&buf,1)//instruct 1 = nombre de structure
			printf("First Process : (write something)");
			scanf("%s", buf);
			sembuf.sem_op = 1;//donne v
		}
	}



	return 0;
}
