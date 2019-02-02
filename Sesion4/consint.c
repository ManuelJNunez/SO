//consumidorFIFO.c
//Consumidor que usa mecanismo de comunicacion FIFO.
#define _DEFAULT_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#define ARCHIVO_FIFO "ComunicacionFIFO"

int main(int argc, char* argv[])
{
int fd;
int buffer;// Almacenamiento del mensaje del cliente.
int leidos;

if(argc != 1){
	printf("Uso: %s\n", argv[0] );
	exit(EXIT_FAILURE);
}

//Crear el cauce con nombre (FIFO) si no existe
umask(0);
mknod(ARCHIVO_FIFO,S_IFIFO|0660,0);
//también vale: mkfifo(ARCHIVO_FIFO,0660);

//Abrir el cauce para lectura-escritura
if ( (fd=open(ARCHIVO_FIFO,O_RDONLY)) <0) {
	perror("open");
	exit(EXIT_FAILURE);
}

//Aceptar datos a consumir hasta que se envíe la cadena fin
while(1) {
	if((leidos=read(fd,&buffer,sizeof(int))) != 0){
		if(buffer == -1){
			close(fd);
			unlink(ARCHIVO_FIFO);
			return EXIT_SUCCESS;
		}
		printf("\nMensaje recibido: %d\n", buffer);
	}
}

return EXIT_SUCCESS;
}





