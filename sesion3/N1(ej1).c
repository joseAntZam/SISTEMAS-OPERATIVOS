#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<dirent.h>
#include<string.h>
#include <stdbool.h>
#include <ftw.h>


int main ( int argc , char *argv[] ){

	pid_t pid_proceso;
	int numero = atoi(argv[1]);

	if(argc!= 2){
		printf("Error en el numero de argumentos pasados\n");
		exit(-1);
	}
	
	
	
	if(setvbuf(stdout,NULL,_IONBF,0)) {
		perror("\nError en setvbuf");
	}
	
	
			
	
	printf("SIN BUFFER*********************************\n");
	
	
	
	if((pid_proceso = fork()) < 0){
		printf("Error en el fork\n");
		exit(-1);
	}
	else if(pid_proceso == 0){
		if(numero%2 == 0){
			printf("El numero %i es par \n",numero);
		}
		else{
			printf("El numero %i no es par \n",numero);
		}
	}
	else{
		if(numero%4 == 0){
			printf("El numero %i es divisible por 4 \n",numero);
		}
		else{
			printf("El numero %i no es divisible por 4 \n",numero);
		}
	}
	
	printf("**********\n");
	
	exit(0);

}
