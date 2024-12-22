#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


int main(int argc, char* argv[]){


	//descriptores de archivos de los ficheros de entrada y de salida
	int entrada, salida;
	
	//vamos a guardar el Bloque n para escribirlo en el fichero
	char bloque[10];
	
	//bytes leídos/escritos
	int bytes = 80;
	
	//escribimos el salto de línea
	char salto_linea[3];
	
	//buffer del que vamos a leer y escribir
	int buffer[81];
	
	//si le hemos pasado un argumento al programa
	if(argc == 2){
		//abrimos el fichero para solo lectura
		entrada = open(argv[1], O_RDONLY);
	}
	//si no le hemos pasado un archivo
	else{
		//cogemos la entrada estándar
		entrada = STDIN_FILENO;
	}
	
	
	//vemos si hemos tenido un problema al abrir el archivo
	if(entrada < 0){
		printf("Error en la apertura del archivo de entrada.");
		exit(-1);
	}
	
	//creamos el archivo de salida
	salida = open("salida.txt", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
	
	//vemos si hemos tenido un problema al crear el archivo
	if(salida < 0){
		printf("Error en la apertura del archivo de salida.");
		exit(-2);
	}
	
	//vamos leyendo hasta que lleguemos a fin de fichero, la condición de parada del for es hasta que read devuelva 0 que será cuando llegue a final de fichero
	
	lseek(salida,31,SEEK_SET);
	write(salida, "\n", sizeof("\n"));
	int numero_bloques;
	
	
	for(int i = 0; read(entrada, buffer, bytes); i++){
	
		int sePuedeAlmacenar = -1;
		for ( int i = 0 ; i < 81 ; i++){
			if(buffer[i] != 0 ){
				sePuedeAlmacenar = 1;
			}
		}
		
		if(sePuedeAlmacenar == 1){
			//para escribir en el archivo Bloque numero cuando vamos a escribir un bloque
			sprintf(bloque, "Bloque %d", i);
			
			write(salida, bloque, sizeof(bloque));
			
			//para escribir salto de línea
			write(salida, "\n", sizeof("\n"));
			
			//escribimos lo que hemos leído de entrada
			write(salida, buffer, bytes);
			
			//para escribir salto de línea
			write(salida, "\n", sizeof("\n"));
			//bl = i;
			
			for ( int i = 0 ; i < 81 ; i++){
				buffer[i]  = 0;
			}
		
		}
		numero_bloques = i ;
	
	}
	
	
	
	char cadenaModificacion[30];
	lseek(salida,0,SEEK_SET);
	sprintf(cadenaModificacion, "Bloque existentes = %d", numero_bloques+1);
	write(salida, cadenaModificacion, sizeof(cadenaModificacion));
}
