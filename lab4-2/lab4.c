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

int pierwsza(int n)
{
	int i,j=0;
	for(i=2;i*i<=n;i++)
	{
		if(n%i == 0) 
			return(0) ;
	}
	return(1);
}

int main(int argc, char ** args)
{	

	int pocz = atoi(args[1]);
	int	kon = atoi(args[2]);
	int	ilosc = atoi(args[3]);

	int grid = (kon-pocz+1)/ilosc;
	int pid, status;

	char tostring[16];
	char tostring2[16];

  	int i = 1;
  	int res;
  	
  	char buf[256];
  	int fildes[2];
  	int num = 0;
  	int counter = 0;
  	
  	pipe(fildes);
  	
	for(i; i <= ilosc ; i++)
	{
		if((pid = fork())==0)
		{
			for(i = pocz; i < pocz+grid; i++)
			{
				if(pierwsza(i)==1)
					num++;	
			}
   			wynik.pocz = pocz;
    		wynik.kon = pocz+grid;
    		wynik.liczba = num;
			printf("Poczatek: %d\t Koniec: %d\t Wynik: %d\n", wynik.pocz, wynik.kon-1, wynik.liczba);
			char tmp_status[16];
			close(fildes[0]);
			write(fildes[1], &wynik, sizeof(wynik));
			close(fildes[1]);
			exit(0);
		}
		pocz = pocz+grid;
	}

 	for(i = 1; i <= ilosc; i++)
 	{
	    pid = wait(&status);
	}
	for(i = 1; i <= ilosc; i++)
 	{
 		
 		read(fildes[0], &wynik, sizeof(wynik));
 		counter = counter + wynik.liczba;
 		
	}
	printf("wynik: %d\n",counter);
	close(fildes[0]);
	close(fildes[1]);
	return 0;
}


