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


#define permisos(mode)((mode  & 011 ) == 011)

struct salida{
	int bytes;
	int archivo;
};

struct salida recorrerDirectorioActual(struct salida resultados, char *ruta_directorio ){
	
	
	DIR *directorio;
	struct dirent *archivo;
	struct stat atributos;
	int permisos_archivo;
	char ruta_directorio_copia[300];


	if( (directorio = opendir(ruta_directorio)) == NULL ){
			printf("\n Error-> %d producido al abrir directorio\n",errno);
			perror("\n Error en open\n");
			exit(-1);
		}
		
		
	while((archivo = readdir(directorio)) != NULL){

		
		sprintf(ruta_directorio_copia ,"%s/%s", ruta_directorio,archivo->d_name);
		
		if(stat(ruta_directorio_copia,&atributos)<0){
			printf("\n Error-> %d producido al abrir directorio\n",errno);
			perror("\n Error en stat\n");
			exit(-1);
		}
		
		permisos_archivo= atributos.st_mode;
		
		if(S_ISREG(permisos_archivo) && permisos(permisos_archivo)){
			resultados.archivo++;
			resultados.bytes += atributos.st_size;
			printf("%s , %lu \n" , ruta_directorio_copia , atributos.st_ino);
			printf("Contador_archivo = %o y Contador_bytes = %o \n" ,resultados.archivo,resultados.bytes);
		}
		
		if(S_ISDIR(permisos_archivo)){
		
			if( strcmp(archivo->d_name, ".")!=0 && strcmp(archivo->d_name, "..")!=0){
				resultados =recorrerDirectorioActual(resultados,ruta_directorio_copia);
			}
		}
		 
		
	} 
	
	return resultados;
}

int main ( int argc , char *argv[]){

	struct salida resultados;
	
	
	if(argc != 2){
		printf("Numero de argumentos incorrecto\n");
		exit(-1);
	}
	
	printf("Los i-nodos son: \n\n");
	
	resultados = recorrerDirectorioActual(resultados,argv[1]);
	
	printf("\nExisten %o archivos regulares con permiso x para grupo y otros\n",resultados.archivo);
	printf("El tamaño total ocupado por dichos archivos es %o bytes\n" , resultados.bytes);	
	
	return 0;
	

}


