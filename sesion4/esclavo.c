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
#include <math.h>


bool esPrimo(int numero){
	bool primo = true;
	
	for ( int i = 3 ; i<sqrt(numero) ; i++){
		if( (numero%i) != 0 ){
			primo = false;
		}
	}
	return primo;
}

int main( int argc , char *argv[]){


if( argc != 3){
	printf("Error en el numero de argumentos pasados\n");
	exit(-1);
}
int inferior = atoi(argv[1]);
int superior = atoi(argv[2]);

for(int i = inferior ; i< superior ; i++){
	if (i < 2 ){
		i = 2;
	}
	if(esPrimo(i)){
		write(STDOUT_FILENO, &i , sizeof(int));
	}
}
return 0;
}

