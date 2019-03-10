#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 


int main(int argc, char *argv[])
{
	int fd;
	int fd2;
	int compteur = 0;

	char * fichtube = "/tmp/tube";
	char * fichtube2 = "/tmp/tube2";
	if(mkfifo("/tmp/tube",S_IRUSR|S_IWUSR|S_IRGRP)== -1)
	{
		perror("mkfifo fail");
		unlink(fichtube);
	}

	mkfifo("/tmp/tube",S_IRUSR|S_IWUSR|S_IRGRP);

	if(mkfifo("/tmp/tube2",S_IRUSR|S_IWUSR|S_IRGRP) == -1)
	{
		perror("mkfifo2 fail");
		unlink(fichtube2);
	}
	mkfifo("/tmp/tube2",S_IRUSR|S_IWUSR|S_IRGRP);

	fd2 = open(fichtube, O_RDONLY);
	fd = open(fichtube2, O_WRONLY);
	
	while(compteur < 1000)
	{
		read(fd2,&compteur,sizeof(int));
		compteur+=1;		
		write(fd,&compteur,sizeof(int));
	}
	
	
	return 0;
}

