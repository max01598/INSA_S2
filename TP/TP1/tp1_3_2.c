#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <fcntl.h> 
#include <sys/stat.h>
#include <sys/types.h>  


int main(int argc, char *argv[])
{
	int fd;
	int fd2;
	int compteur = 0;
	float debit = 0;
	clock_t clockdepart;
	clock_t clockfin;

	char * fichtube = "/tmp/tube";
	char * fichtube2 = "/tmp/tube2";
	if(mkfifo(fichtube,S_IRUSR|S_IWUSR|S_IRGRP) == -1)
	{
		perror("mkfifo fail");
	}
	if(mkfifo(fichtube2,S_IRUSR|S_IWUSR|S_IRGRP) == -1)
	{
		perror("mkfifo2 fail");
	}

	fd = open(fichtube2, O_RDONLY);
	fd2 = open(fichtube, O_WRONLY);

	clockdepart = clock();
	while(compteur<1000)
	{			
		/* Ecriture */
		compteur =+1 ;
		write(fd2,&compteur, sizeof(int));

		/* Lecture */
		read(fd,&compteur,sizeof(int));
	}
	unlink(fichtube);
	unlink(fichtube2);
	clockfin = clock();
	double duree = (double)(clockfin-clockdepart)/CLOCKS_PER_SEC;
	debit = (int)(1000*2*4*8)*pow(10,-6)/duree;
	printf("debit : %f Mega par seconde\n",debit);
	return 0;
}

