#include<sys/types.h>	
#include<sys/wait.h>	
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

int main(){
	int estado, procs = 5, hijos = procs;
	int pids[procs];

	for(int i = 0; i < procs; ++i){
		if((pids[i] = fork()) == -1){
			perror("\n Error en el fork() ");
			exit(EXIT_FAILURE);
		}else if (!pids[i]){
			printf("Soy el hijo %d\n", getpid());
			exit(EXIT_SUCCESS);
		}
	}

	for(int i = 0; i < procs; i+=2){
		waitpid(pids[i], &estado, 0);

		printf("Acaba de finalizar mi hijo con PID: %d\n", pids[i]);
		printf("Sólo me quedan %d hijos vivos.\n", --hijos);
	}

	for(int i = 1; i < procs; i+=2){
		waitpid(pids[i], &estado, 0);

		printf("Acaba de finalizar mi hijo con PID: %d\n", pids[i]);
		printf("Sólo me quedan %d hijos vivos.\n", --hijos);
	}

	exit(EXIT_SUCCESS);
}