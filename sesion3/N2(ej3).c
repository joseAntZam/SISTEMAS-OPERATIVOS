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

int main(int argc, char *argv[]){
	int i;
	int nprocs=5;
	pid_t childpid;

	
	for (i=1 ; i<=nprocs ; i++) {
		if ((childpid=fork()) == -1) {
			fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
			exit(EXIT_FAILURE);
		}

		if (!childpid)
			break;
	}
	
	if (childpid == 0){
		printf("Hijo: %d  -- Padre:%d\n", getpid(), getppid() );
	}

	
	
	return 0;
}
