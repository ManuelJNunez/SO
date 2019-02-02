#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>		//Needed for open
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

void buscardir(DIR* dir, const char* pathname, int *nbytes, int *narchivos){
	struct stat atributos;
	struct dirent *entrada;
	char str[300];

	while((entrada = readdir(dir)) != NULL){
		if((strcmp(entrada->d_name, ".") != 0) && (strcmp(entrada->d_name,"..") != 0)){
			sprintf(str,"%s/%s", pathname, entrada->d_name);

			if(stat(str,&atributos) < 0){
				perror("\nError en stat()");
				exit(EXIT_FAILURE);
			}

			if(S_ISDIR(atributos.st_mode)){
				if((dir = opendir(str)) != NULL)
					buscardir(dir, str, nbytes, narchivos);
			}else if(S_ISREG(atributos.st_mode)){
				if((atributos.st_mode & (S_IXGRP | S_IXOTH)) == (S_IXGRP | S_IXOTH)){
					printf("%s %ld\n", str, entrada->d_ino);
					(*nbytes) += (int)atributos.st_size;
					(*narchivos)++;
				}
			}
		}
	}
}

int main(int argc, char *argv[]){
	DIR* dir;
	int nbytes, narchivos;
	char pathname[50];

	nbytes = narchivos = 0;

	if(argc == 2)
		strcpy(pathname, argv[1]);
	else
		strcpy(pathname, ".");

	if((dir = opendir(pathname)) == NULL){
		perror("Error en opendir()");
		exit(EXIT_FAILURE);
	}

	printf("Los inodos son:\n");
	buscardir(dir, pathname, &nbytes, &narchivos);
	printf("Existen %d archivos regulares con permiso x para grupo y otros.\n", narchivos);
	printf("El tamaño total ocupado por estos archivos es de %d bytes.\n", nbytes);

	return EXIT_SUCCESS;
}