/*
ejercicio2.c
Bloque 1
//Aquí van los primeros 80 Bytes del archivo pasado como argumento.

*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>  	/* Primitive system data types for abstraction\
			   of implementation-dependent data types.
			   POSIX Standard: 2.6 Primitive System Data Types
			   <sys/types.h>
			*/
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include <string.h>

#define BUFFER_TAMA 80
#define STR_TAMA 15

char buffer[BUFFER_TAMA];
char str[STR_TAMA];
char str1[30];

int main(int argc, char* argv[])
{
int out_fd, in_fd;
int bufferTama = BUFFER_TAMA * sizeof(char);

if(argc != 2){
	printf("USAGE: \n %s pathname \n",argv[0]);
	exit(EXIT_FAILURE);
}

if( (in_fd=open(argv[1],O_RDONLY)) < 0){
	perror("\nError en open(): ");
	exit(EXIT_FAILURE);
}

if( (out_fd=open("archivo",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0) {
	perror("\nError en segundo open(): ");
	exit(EXIT_FAILURE);
}

int i = 1;
int leidos = 0;

if(lseek(out_fd,30, SEEK_SET) < 0){
	perror("\nError en lseek(): ");
	exit(EXIT_FAILURE);
}

while((leidos=read(in_fd,buffer,bufferTama)) != 0){
	sprintf(str,"\nBloque %i\n",i);
	if((unsigned)write(out_fd,str,strlen(str)*sizeof(char)) != (unsigned)strlen(str)*sizeof(char)){
		perror("\nError en write() de bloque");
		exit(EXIT_FAILURE);
	}

	if(write(out_fd,buffer,leidos) != leidos){
		perror("\nError en write() de chunk de 80");
		exit(EXIT_FAILURE);
	}
	++i;
}

sprintf(str1, "El numero de bloques es %d\n", i-1);

if(lseek(out_fd, 0, SEEK_SET) < 0){
	perror("\n Error en lseek(): ");
	exit(EXIT_FAILURE);
}

if((unsigned)write(out_fd, str1, strlen(str1)*sizeof(char)) != (unsigned)strlen(str1)*sizeof(char)){
	perror("\nError en write(): ");
	exit(EXIT_FAILURE);
}

close(in_fd);
close(out_fd);

return EXIT_SUCCESS;
}
