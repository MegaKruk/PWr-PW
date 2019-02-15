#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char * argv[]) 
{
	int id, i;
	for(i=1; i <= atoi(argv[2]); i++) 
	{ 
		printf("Proces: %d, Krok: %d \n", atoi(argv[1]), i); 
		sleep(1); 
	} 
	exit(i); 
}
