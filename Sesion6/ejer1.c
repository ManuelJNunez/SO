#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	int fd;
	if(argc != 4){
		printf("Uso: ./ejer1 orden [<>] archivo\n");
		exit(EXIT_FAILURE);
	}

	if(strcmp(argv[2],">") == 0){
		if((fd=open(argv[3],O_CREAT|O_WRONLY)) < 0 ){
			perror("\nError en open()");
			exit(EXIT_FAILURE);
		}

		close(STDOUT_FILENO);

		if(fcntl(fd, F_DUPFD, STDOUT_FILENO) < 0){
			perror("\nError en fcntl()");
			exit(EXIT_FAILURE);
		}

		if(execlp(argv[1], argv[1], NULL) < 0){
			perror("Fallo en exec()");
			exit(EXIT_FAILURE);
		}
	}
	else if (strcmp(argv[2],"<") == 0){
		if((fd=open(argv[3],O_CREAT|O_RDONLY)) < 0 ){
			perror("\nError en open()");
			exit(EXIT_FAILURE);
		}

		close(STDIN_FILENO);

		if(fcntl(fd, F_DUPFD, STDIN_FILENO) < 0){
			perror("\nError en fcntl()");
			exit(EXIT_FAILURE);
		}

		if(execlp(argv[1], argv[1], NULL) < 0){
			perror("Fallo en exec()");
			exit(EXIT_FAILURE);
		}
	}

	return EXIT_SUCCESS;
}