#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include <math.h>

int main(int argc, char *argv[]){
	if(argc != 3){
		printf("Error en el programa esclavo.\nIntenta usar ./esclavo <ini> <fin>\n");
		exit(EXIT_FAILURE);
	}

	int ini,fin, escritos, esprimo;

	esprimo = 1;
	ini = (int)strtol(argv[1], NULL, 10);
	fin = (int)strtol(argv[2], NULL, 10);

	for(int i = ini; i <= fin; ++i){
		int maxdiv = sqrt(i);

		for(int j = 2; j <= maxdiv && esprimo; ++j){
			if(i%j == 0)
				esprimo = 0;
		}

		if(esprimo == 1){
			if((escritos = write(STDOUT_FILENO, &i, sizeof(int))) != sizeof(int)){
				perror("Error en write()");
				exit(EXIT_FAILURE);
			}
		}else
			esprimo = 1;
	}

	return EXIT_SUCCESS;
}