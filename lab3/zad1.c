#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

// #include "process.h"
int main(int argc, char * argv[])
{ 
	int pid, status, lp, i, j, k, l; 
	lp = argc - 2;
	printf("Instrukcja wspolna\n");
	for(i=1;i<=lp;i++) 
	{
		if((pid = fork()) == 0) 
		{
			for(j = 1; j <= atoi(argv[i]); j++)
			{
				printf("Proces: %d, Krok: %d\n", i, j);
				sleep(1);
			}
			exit(i);
		}  
	}	
	for(k=1; k <= atoi(argv[1]); k++) 
		{ 
			printf("Macierzysty, Krok %d \n",k); 
			sleep(1); 
		} 
	for(int l = 1; l < argc; l++)
	{
		pid = wait(&status);
		printf("Proces %d zakończony, status %d\n", pid,WEXITSTATUS(status)); 
	}
	exit(0);
	return 0; 
}
