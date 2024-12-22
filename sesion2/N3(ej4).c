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


#define permisos(mode)(((mode & ~ S_IFMT) & 011 ) == 011)

int archivo = 0;
int bytes = 0;

int recorrerDirectorioActual(const char *pathname , const struct stat *statbuf , int typeflag , struct FWT* ftwbuf){
	
		
		if(S_ISREG(statbuf->st_mode) && permisos(statbuf->st_mode)){
			archivo++;
			bytes += statbuf->st_size;
			printf("%s , %lu \n" , pathname, statbuf->st_ino);
			printf("Contador_archivo = %o y Contador_bytes = %o \n" ,archivo,bytes);
		}
		
		
	return 0;	
	} 
	
	


int main ( int argc , char *argv[]){

	
	
	if(argc != 2){
		printf("Numero de argumentos incorrecto\n");
		exit(-1);
	}
	
	printf("Los i-nodos son: \n\n");
	
	if(nftw(argv[1],recorrerDirectorioActual, 10, 0) != 0){
		printf("Error en ntfw");
		exit(-1);
	}
	
	printf("\nExisten %o archivos regulares con permiso x para grupo y otros\n",archivo);
	printf("El tamaño total ocupado por dichos archivos es %o bytes\n" ,bytes);	
	
	return 0;
	

}


