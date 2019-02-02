#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(){
	int pid, nprocs = 5;
	for(int i=1; i < nprocs; i++) {
		if ((pid= fork()) == -1) {
			perror("\nError en el fork");
			exit(EXIT_FAILURE);
		}
		if(pid)
			break;
	}

	if(pid == 0)
		printf("Hola, soy el hijo con id %d mi padre es: %d\n", getpid(), getppid());
	else
		printf("Hola, soy el padre con id %d y mi hijo tiene id %d\n", getpid(), pid);

	return EXIT_SUCCESS;
}