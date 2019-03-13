#include <stdio.h> 
#include <pthread.h> 
#include <sys/sem.h> 
#include <unistd.h>
#include <sys/shm.h>


int main()
{

	int coompteur = 0;
	key_t key = 23;//identifie le semaphore pour le partage
	key_t key2 = 24;
	key_t keyMem = 1;//identifie la shm 
	int semaphoreR;
	int semaphoreW;
	int addr;
	char buf[10];

	semaphoreR = semget(key,1,0666|IPC_CREAT);
	union semum sem;//arg de semctl
	sem.val = 0;
	semctl(semaphoreR,0,SETVAL,sem)//initilise la valeur initiale du sémaphore SETVAL + initialisation

	/***** P ****/
	struct sembuf buf;//structure pour operation p ou v
	buf.sem_num = 0;
	buf.sem_op = -1;//donne p
	buf.sem_flag = 0;

	semaphoreW = semget(key2,1,0666|IPC_CREAT);
	union semum sem2;//arg de semctl
	sem2.val = 1;
	semctl(semaphoreW,0,SETVAL,sem2)//initilise la valeur initiale du sémaphore SETVAL + initialisation
	/**** V **/
	struct sembuf buf2;//structure pour operation p ou v
	buf2.sem_num = 0;
	buf2.sem_op = 1;//donne v
	buf2.sem_flag = 0;

		
	int shm;//creation de la mémoire partagé
	shm = shmget(keyMem, sizeof(int),0666|IPC_CREAT);
	addr = shmat(shm,0,0);

		
	while(compteur < 1000)
	{
		//wait de l'ecriture donc p
		semop(semaphoreR,&buf,1);
		//V pour la lecture
		semop(semaphoreW,&buf2,1);
		//read
		read(addr,&compteur,sizeof(int));
		compteur = compteur +1;
		printf("Dans P2 : %d",compteur);
		//write
		write(addr,&compteur, sizeof(int));
		//V pour attendre lecritute de P1
		semop(semaphoreR, &buf2,1);
		//P pour bloqué lecture de P1
		semop(semaphoreW, &buf,1);
	}
	shmdt(addr);
	return 0;
}
