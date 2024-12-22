#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>		// Needed for DIR
#include <errno.h>
#include <sys/stat.h>

#define BASE_OCT 8

int main(int argc, char *argv[]){
	DIR *directorio;
	int permisos_nuevos, permisos_antiguos;
	struct dirent *archivo;
	struct stat atributos;
	char ruta_archivo[300];

	if(argc != 3){
		printf("\nSintaxis de ejecución: ejercicio2 [<nom_directorio>] [<núm_octal_4_dígitos>]\n\n");
		exit(-1);
	}

	// Comprobar que existe el directorio
	if ( (directorio = opendir(argv[1])) == NULL){
		printf("Error %d al abrir el directorio %s.\n", errno, argv[1]);
		perror("\nError en opendir\n");
		exit(-1);
	}

	// Nuevos permisos en octal
	permisos_nuevos = strtol(argv[2], NULL, BASE_OCT);


	while( (archivo = readdir(directorio)) != NULL){
	
		sprintf(ruta_archivo, "%s/%s", argv[1], archivo->d_name);

		// Acceso a datos del archivo
		if(stat(ruta_archivo,&atributos) < 0) {
			printf("\nError %d al intentar acceder a los atributos de %s",errno,ruta_archivo);
			perror("\nError en stat");
			exit(-1);
		}

		permisos_antiguos = atributos.st_mode;

		// Cambio de permisos
		if( !S_ISDIR(atributos.st_mode) ){
			if(chmod(ruta_archivo, permisos_nuevos) < 0) {
				printf("%s : %d %o\n",ruta_archivo,errno,permisos_antiguos);
				exit(-1);
			}else{
				printf("%s : %o %o\n",ruta_archivo,permisos_antiguos,permisos_nuevos);
			}			
		}
	}

	if( closedir(directorio) != 0){
		printf("Error %d al cerrar el directorio %s\n",errno,argv[1]);
		perror("Error en closedir");
		exit(-1);
	}

	return -1;
}
