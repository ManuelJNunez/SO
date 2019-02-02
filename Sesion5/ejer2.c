#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

static int contadores[32] = {0};

static void handler(int sigNum){
	contadores[sigNum]++;
	printf("La señal %d se ha recibido %d veces.\n", sigNum, contadores[sigNum]);
}

int main(){
	struct sigaction sa;

	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;

	if(sigemptyset(&sa.sa_mask) < 0){
		perror("Error en sigemtyset()");
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < 32;++i){
		if(sigaction(i, &sa, NULL) < 0){
			perror("Error en sigaction()");
		}
	}

	while(1);
}