#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

int main(){
	FILE *fdtmp;
	char leido[1024];
	int fdblock, tam, leidos;
	struct flock cerrojo;

	if((fdtmp = tmpfile()) == NULL){
		perror("\nError en tmpfile()");
		exit(EXIT_FAILURE);
	}

	if((fdblock = open("Bloqueo", O_CREAT | O_WRONLY, 0700)) < 0){
		perror("\nError en open()");
		exit(EXIT_FAILURE);
	}

	cerrojo.l_type = F_WRLCK;
	cerrojo.l_whence = SEEK_SET;
	cerrojo.l_start = 0;
	cerrojo.l_len = 0;

	while((tam = read(STDIN_FILENO, leido, 1024)) > 0){
		fwrite(leido, sizeof(char), tam, fdtmp);
	}

	if(fcntl(fdblock, F_SETLKW, &cerrojo) < 0){
		perror("\nError al establecer cerrojo");
		exit(EXIT_FAILURE);
	}

	if(fseek(fdtmp, 0, SEEK_SET) < 0){
		perror("\nError en fseek()");
		exit(EXIT_FAILURE);
	}

	while(!feof(fdtmp)){
		tam = fread(leido, sizeof(char), 1024, fdtmp);
		if((leidos = write(STDOUT_FILENO, leido, tam)) != tam){
			perror("\nError en write()");
			exit(EXIT_FAILURE);
		}
	}

	printf("\n");

	cerrojo.l_type = F_UNLCK;

	if(fcntl(fdblock, F_SETLKW, &cerrojo) < 0){
		perror("\nError al abrir cerrojo");
		exit(EXIT_FAILURE);
	}

	unlink("Bloqueo");

	return EXIT_SUCCESS;
}