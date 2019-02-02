#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(int argc, char *argv[]){
	const int NESCLAVOS = 2;
	int fd0[2], fd1[2];
	char inicio[10], fin[10];
	pid_t pid;

	if(argc != 3){
		printf("Orden inválida.\nPrueba con ./ejer5 <num1> <num2>\n");
		exit(EXIT_FAILURE);
	}

	int num1 = (int)strtol(argv[1], NULL, 10);
	int num2 = (int)strtol(argv[2], NULL, 10);

	if(num1 > num2){
		printf("El primer número debe ser menor que el segundo.\n");
		exit(EXIT_FAILURE);
	}

	int rango = num2 - num1;
	pipe(fd0);
	pipe(fd1);

	int i;
	for(i = 0; i < NESCLAVOS; ++i){
		if((pid = fork()) < 0){
			perror("Error en el fork()");
			exit(EXIT_FAILURE);
		}

		if(!pid)
			break;
	}

	if(pid == 0){
		if(i == 0 ){
			sprintf(inicio, "%d", num1);
			sprintf(fin, "%d", (num1+(rango/2)));
			close(fd1[0]);
			close(fd1[1]);
			dup2(fd0[1],STDOUT_FILENO);
		}else if(i == 1){
			sprintf(inicio, "%d", (num1+(rango/2)+1));
			sprintf(fin, "%d", num2);
			close(fd0[0]);
			close(fd0[1]);
			dup2(fd1[1],STDOUT_FILENO);
		}

		if(execl("./esclavo", "esclavo", inicio, fin, NULL) < 0){
			perror("Error en exec()");
			exit(EXIT_FAILURE);
		}
	}else{
		int numbytes, val;

		close(fd0[1]);
		close(fd1[1]);

		while((numbytes = read(fd0[0], &val, sizeof(int))) != 0)
			printf("%d ", val);

		while((numbytes = read(fd1[0], &val, sizeof(int))) != 0)
			printf("%d ", val);

		printf("\n");
	}

	return EXIT_SUCCESS;
}