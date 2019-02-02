#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>


static void manejador(){
	int estado;
	wait(&estado);
}

int main(int argc, char* argv[]){
	if(argc != 2){
		printf("Uso: %s <nombrefifo>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	signal(SIGCHLD, manejador);

	char nombrefifoe[50], nombrefifos[50];
	int dfE, dfS, le, pidcliente, pid;

	sprintf(nombrefifoe, "%se", argv[1]);
	sprintf(nombrefifos, "%ss", argv[1]);

	mkfifo(nombrefifoe, S_IRWXU);
	mkfifo(nombrefifos, S_IRWXU);

	if((dfE = open(nombrefifoe, O_RDWR)) < 0){
		perror("\nError en open()");
		exit(EXIT_FAILURE);
	}

	if((dfS = open(nombrefifos, O_RDWR)) < 0){
		perror("\nError en open()");
		exit(EXIT_FAILURE);
	}

	while((le=read(dfE, &pidcliente, sizeof(int))) != 0){
		if((pid = fork()) < 0){
			perror("\nError en fork()");
			exit(EXIT_FAILURE);
		}

		if(pid == 0){
			char str[50];
			int pidproxy = getpid(), fdproxy, escritos;

			sprintf(str, "fifo.%d", pidproxy);
			mkfifo(str, S_IRWXU);

			if((escritos = write(dfS, &pidproxy, sizeof(int))) != sizeof(int)){
				perror("\nError en write()");
				exit(EXIT_FAILURE);
			}
			
			if((fdproxy = open(str, O_RDONLY)) < 0){
				perror("\nError en open()");
				exit(EXIT_FAILURE);
			}

			dup2(fdproxy, STDIN_FILENO);

			if(execlp("./proxy", "proxy", NULL) < 0){
				perror("Error en exec()");
				exit(EXIT_FAILURE);
			}
		}
	}

	return EXIT_SUCCESS;
}