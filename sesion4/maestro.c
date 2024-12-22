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


int main (int argc , char *argv[]){


	int fd_1[2];
	int fd_2[2];

	pid_t PID_esclavo1;
	pid_t PID_esclavo2;
	
	char ini1[6] , fin1[6] , ini2[6] , fin2[6];
	int mitad;
	int buffer;
	int numeroBytes;


	if(argc != 3){
		printf("Error en el numero de argumentos\n");
		exit(-1);
	}
	
	int inferior = atoi(argv[1]);
	int superior = atoi(argv[2]);
	
	if(inferior >= superior){
		printf("Error al pasar el intervalo , de terner el formato inferior-superior");
		exit(-1);
	}

	if( (superior - inferior) % 2 == 0 ){
		mitad = inferior + ((superior-inferior)/2);
	}
	else{
		mitad = inferior + ((superior-inferior +1 )/2);
	}
	
	sprintf(ini1 ,"%i", inferior);
	sprintf(fin1 , "%i", mitad);
	sprintf(ini2 ,"%i", mitad+1);
	sprintf(fin2 , "%i", superior);

	pipe(fd_1);
	pipe(fd_2);


	if((PID_esclavo1 = fork()) < 0 ){
		perror("fork\n");
		exit(-1);
	}

	if(PID_esclavo1 == 0){
		
		
		close(fd_1[0]);
		dup2(fd_1[1] ,STDOUT_FILENO);
		execlp("./esclavo_ejecutable","esclavo_ejecutable" , ini1 , fin1 ,NULL);

	}
	else{

	
		close(fd_1[1]);
		while( (numeroBytes = read(fd_1[0], &buffer , sizeof(int))) == 4 ){
			printf("%i\n",buffer);
		}
		
		close(fd_1[0]);
		
		
		if((PID_esclavo2 = fork()) < 0 ){
			perror("fork\n");
			exit(-1);
		}
		
		if(PID_esclavo2 == 0){
			close(fd_2[0]);
			dup2(fd_2[1],STDOUT_FILENO);
			execlp("./esclavo_ejecutable","esclavo_ejecutable", ini2 , fin2,NULL);
		}
		else{
			close(fd_2[1]);
			while((numeroBytes = read(fd_2[0] , &buffer , sizeof(int))) == 4){
				printf("%i\n" , buffer);
			}
			close(fd_2[0]);
		
		}
	}
return 0;

}


