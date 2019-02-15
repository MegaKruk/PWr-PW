#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

struct  
{
		int pocz;
		int kon;
		int liczba;
} wynik;

int main(int argc, char ** args)
{	

	int pocz = atoi(args[1]);
	int	kon = atoi(args[2]);
	int	ilosc = atoi(args[3]);

	int grid = (kon-pocz+1)/ilosc;
	int pid, status;

	char tostring[16];
	char tostring2[16];

  	int i = 0;
  	int res;
  	
  	int plik = open("plik.txt", O_RDWR | O_CREAT | O_TRUNC,0666) ;
	
	if(plik < 0)
	{
		perror("error!");
	}
  	
	for(i; i < ilosc ; i++)
	{
		sprintf(tostring, "%d", pocz);
		sprintf(tostring2, "%d", pocz + grid);

		if((pid = fork())==0)
		{
			execl("./potomny","potomny", tostring, tostring2, NULL);
			perror("error");
		}
		pocz+=grid;
	}

	int counter = 0; 
	int rd;

 	for(i = 0; i < ilosc; i++)
 	{
	    pid = wait(&status);
	}
		

	for(i = 0; i < ilosc; i++)
 	{
 		res = lockf(plik, F_LOCK, 0);
 		rd = read(plik, &wynik, sizeof(wynik));
 		res = lockf(plik, F_ULOCK, 0); 
 		printf("Poczatek: %d\t Koniec: %d\t Wynik: %d\n", wynik.pocz, wynik.kon-1, wynik.liczba);
 		counter = counter + wynik.liczba;
	}

	printf("%d\n", counter);	
	close(plik);
	return 0;
}

