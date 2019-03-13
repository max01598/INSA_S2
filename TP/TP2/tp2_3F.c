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

int main(int argc, char * argv[])
{
	int * compteur = 0;
	int semaphore;
	key_t key = 23;//identifie le semaphore pour le partage
	key_t keyMem = 1;//identifie la shm
	union semun sem;//arg de semctl
	union semun sem2;//arg de semctl
	
	semaphore = semget(key,2,0666|IPC_CREAT);//0 = ecriture et 1 = lecture
	
	/***** Semaphore 0 ****/
	struct sembuf buf;//structure pour operation p ou v
	

	/**** Semaphore 1 ***/
	struct sembuf buf2;//structure pour operation p ou v
	

	int shm;//creation de la mémoire partagé
	shm = shmget(keyMem, sizeof(int),0666|IPC_CREAT);
	compteur = shmat(shm,0,0);
	(*compteur) = 0;
	if(atoi(argv[1]) == 1)
	{
		
		sem.val = 0;
		semctl(semaphore,0,SETVAL,sem);//initilise la valeur initiale du sémaphore SETVAL + initialisation
		sem.val = 0;
		semctl(semaphore,1,SETVAL,sem);//initilise la valeur initiale du sémaphore SETVAL + initialisation
		
		while((*compteur) < 10)
		{
			//write
			(*compteur)++;
			buf.sem_num = 0;
			buf.sem_op = -1;//donne v
			buf.sem_flg = 0;
			semop(semaphore,&buf,1);//liberer le semaphore pour la lecture de P2

			//wait que P2 est ecrit
			buf2.sem_num = 1;
			buf2.sem_op = 1;//donne p
			buf2.sem_flg = 0;
			semop(semaphore,&buf2,1);//prendre le semaphore
			//read
			printf("P1 -> compteur %d \n",(*compteur));
		}
	}
	else
	{
		while((*compteur) < 10)
		{
			buf.sem_num = 0;
			buf.sem_op = -1;//donne p
			buf.sem_flg = 0;
			//wait de l'ecriture donc p
			semop(semaphore,&buf,1);
			//read
			printf("P2 -> compteur %d \n",(*compteur));
			//write
			(*compteur)++;
			//V pour la lecture
			buf2.sem_num = 1;
			buf2.sem_op = 1;//donne v
			buf2.sem_flg = 0;
			semop(semaphore,&buf2,1);
		}
	}
	semctl(semaphore, 0, IPC_RMID);
	semctl(semaphore, 1, IPC_RMID);
	shmdt(compteur);
	return 0;
}
