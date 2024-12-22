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


const int numero_proceso = 5;
int main ( int argc , char *argv[]){

	int pids_procesos[numero_proceso];
	int numero_hijos;
	int estado;


	if(setvbuf(stdout,NULL,_IONBF,0)){
		perror("\nError en setvbuf");
	}

	for(int i = 0 ; i < numero_proceso ; i++){
		
		if((pids_procesos[i] = fork())< 0){
			printf("Error en fork\n");
			exit(-1);
			}
		
		if(pids_procesos[i] == 0){
			printf("Soy el hijo: %d-------%d\n" , getpid(),getppid() );
			exit(estado);
			}
		numero_hijos++;
	}

	sleep(2);

	for(int i = 0 ; i< numero_proceso ; i++){
		
		waitpid(pids_procesos[i],&estado,0);
		numero_hijos--;
		
		printf("Acaba de finalizar mi hijo con PID %i\n",pids_procesos[i]);
		printf("Solo me quedan %i hijos vivo\n",numero_hijos);

	}
	return 0;
}
