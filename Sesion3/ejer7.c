#include<sys/types.h>	
#include<sys/wait.h>	
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]){
	pid_t pid;
	int estado;
	char* args[50];

	for(int i = 0; i < argc-2; ++i){
		strcpy(args[i], argv[i+1]);
	}

	if((strcmp(args[argc-2], "bg")) == 0){
		args[argc-2] = (char*) NULL;
		if( (pid=fork())<0) {
			perror("\nError en el fork");
			exit(EXIT_FAILURE);
		}
		else if(pid==0) {  //proceso hijo ejecutando el programa
			if( (execvp(args[0],args)) < 0) {
				perror("\nError en el execl");
				exit(EXIT_FAILURE);
			}
		}	
		wait(&estado);

		printf("\nMi hijo %d ha finalizado con el estado %d\n",pid,estado>>8);
	}else{
		if((execvp(args[0], args)) < 0){
				perror("\nError en el execl");
				exit(EXIT_FAILURE);
		}
	}

	exit(EXIT_SUCCESS);
}
