#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h> 
#include <sys/sem.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h> 


union semun {
	int val; /* valeur pour SETVAL */
	struct semid_ds *buf; /* tampon pour IPC STAT, IPC SET */
	unsigned short int *array; /* tableau pour GETALL, SETALL */
	struct seminfo * buff; /* tampon pour IPC INFO */
};


int main(int argc, char* argv[])
{
	key_t key = 23;//identifie le semaphore pour le partage 
	int semaphore;
	semaphore = semget(key,1,0666|IPC_CREAT);
	if(semaphore == -1)
	{
		perror("erreur");
		exit(1);
	}

	

	struct sembuf sembuf;//structure pour operation p ou v
	/*sembuf.sem_num = 0;
	sembuf.sem_op = -1;//donne p
	sembuf.sem_flg = 0;*/
	
	if(atoi(argv[1])==1){
		union semun sem;//arg de semctl
		sem.val = 1;
		semctl(semaphore,0,SETVAL,sem);//initilise la valeur initiale du sémaphore SETVAL + initialisation
		char buf[10];
		while(1)
		{
				
			sembuf.sem_num = 0;
			sembuf.sem_op = -1;//donne p
			sembuf.sem_flg = 0;
			semop(semaphore,&sembuf,1);//instruct 1 = nombre de structure
			printf("First Process : (write something)");
			scanf("%s", buf);
			sembuf.sem_op = 1;//donne v
			semop(semaphore,&sembuf,1);
		}
	}else{
		char buf[10];
		while(1)
		{
			sembuf.sem_num = 0;
			sembuf.sem_op = -1;//donne p
			sembuf.sem_flg = 0;
			semop(semaphore,&sembuf,1);//instruct 1 = nombre de structure
			printf("Second Process : (write something)");
			scanf("%s", buf);
			sembuf.sem_op = 1;//donne v
			semop(semaphore,&sembuf,1);
		}
	}
	semctl(semaphore, 0, IPC_RMID);
	return 0;
}
