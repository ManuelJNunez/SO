#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
	if(argc != 4){
		printf("Uso: %s <orden1> \"|\" <orden2>\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	if(strcmp(argv[2],"|") != 0){
		printf("Uso: %s <orden1> \"|\" <orden2>\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	int fd[2], pid;
	pipe(fd);

	if((pid = fork()) < 0){
		perror("\nError en fork()");
		exit(EXIT_FAILURE);
	}

	if(pid == 0){
		close(fd[0]);
		close(STDOUT_FILENO);
		if(fcntl(fd[1],F_DUPFD, STDOUT_FILENO) < 0){
			perror("\nError en fcntl()");
			exit(EXIT_FAILURE);
		}

		if((execlp(argv[1], argv[1], NULL)) < 0){
			perror("\nError en execlp()");
			exit(EXIT_FAILURE);
		}
	}else{
		close(fd[1]);
		close(STDIN_FILENO);
		if(fcntl(fd[0],F_DUPFD, STDIN_FILENO) < 0){
			perror("\nError en fcntl()");
			exit(EXIT_FAILURE);
		}

		if((execlp(argv[3], argv[3], NULL)) < 0){
			perror("\nError en execlp()");
			exit(EXIT_FAILURE);
		}
	}

	return EXIT_SUCCESS;
}