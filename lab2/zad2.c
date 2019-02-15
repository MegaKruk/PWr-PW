#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{ 
	int pid, i, j, status, lp, k, l; 
	char kroki[20]; 
	
	lp = argc - 2;
	printf("Instrukcja wspolna\n");
	
	for(i=1;i<=lp;i++) 
	{
		if((pid = fork()) == 0) 
		{ 	
			sprintf(kroki, "%d", i);
			execl("/home/lstudent/pot","pot", kroki, argv[i], NULL); // EXECL
			perror("Blad funkcji exec");      
		} 	 
	}
	
	for(k=1; k <= atoi(argv[1]); k++) 
	{ 
		printf("Macierzysty - krok %d \n",k); 
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
