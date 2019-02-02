#include<sys/types.h>	
#include<sys/wait.h>	
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

int main(){
	pid_t pid;
	int estado, procs = 5;

	for(int i = 0; i < procs; ++i){
		if((pid = fork()) == -1){
			perror("\n Error en el fork() ");
			exit(EXIT_FAILURE);
		}else if (!pid){
			break;
		}
	}

	if(pid == 0){
		printf("Soy el hijo %d\n", getpid());
	}else{
		for(int i = procs-1; i >= 0; --i){
			pid = wait(&estado);

			printf("Acaba de finalizar mi hijo con PID: %d\n", pid);
			printf("Sólo me quedan %d hijos vivos.\n", i);
		}
	}

	exit(EXIT_SUCCESS);
}