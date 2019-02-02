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

int main(int argc, char** argv){
	DIR *dir;
	int perm;
	struct stat atributos;
	struct dirent *entrada;
	char str[300];

	if(argc == 3){
		perm = (int) strtol(argv[2], NULL, 8);
		dir = opendir(argv[1]);
	}else{
		printf("Uso: ./ejer2 <pathname> <permisos>\n");
		exit(EXIT_FAILURE);
	}

	while((entrada = readdir(dir)) != NULL){
		if(strcmp(entrada->d_name, ".") != 0){
			sprintf(str,"%s/%s", argv[1], entrada->d_name);

			if(stat(str,&atributos) < 0){
				perror("Error en stat()");
				exit(EXIT_FAILURE);
			}

			if(S_ISREG(atributos.st_mode)){
				int old_perm = atributos.st_mode & 0777;

				printf("<%s> : <%o>", str, old_perm);
			
				if(chmod(str,perm) < 0){
					perror("\nError en chmod");
					exit(EXIT_FAILURE);
				}else{
					stat(str, &atributos);
					printf("<%o> \n",atributos.st_mode & 0777);
				}
			}
		}		
	}

	return EXIT_SUCCESS;
}