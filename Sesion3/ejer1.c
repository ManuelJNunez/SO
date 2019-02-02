#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char *argv[]){
	int pid;

	if(argc != 2){
		printf("Uso: ./ejer1 <valor>.\n");
		exit(EXIT_FAILURE);
	}

	int numero = (int)strtol(argv[1], NULL, 10);

	if((pid = fork()) < 0){
		perror("\nError en fork");
		exit(EXIT_FAILURE);
	}else if(pid == 0){
		printf("Hola, soy el proceso hijo, me encargo de ver si el valor es par o no.\n");

		if(numero % 2 == 0)
			printf("El número introducido es par.\n");
		else
			printf("El número introducido es impar.\n");
	}else if(pid != 0){
		printf("Hola, soy el padre, me encargo de ver si el número es divisible por 4 o no.\n");

		if(numero % 4 == 0)
			printf("Es divisible por 4.\n");
		else
			printf("No es divisible por 4.\n");
	}

	return EXIT_SUCCESS;
}