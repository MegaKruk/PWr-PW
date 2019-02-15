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


int pierwsza(int n);

int main(int argc,char ** args)
{
	int plik = open("plik.txt", O_RDWR | O_APPEND) ;

	int pocz = atoi(args[1]);
	int kon = atoi(args[2]);
	int i = 0;
	int liczba = 0;
	int res;
	
	for(i = pocz; i < kon; i++)
	{
		if(pierwsza(i)==1)
			liczba++;	
	}
    wynik.pocz = pocz;
    wynik.kon = kon;
    wynik.liczba = liczba;

	char tmp_status[16];
	sprintf(tmp_status, "%d\n", liczba);
	res = lockf(plik, F_LOCK, 0);
	write(plik, &wynik, sizeof(wynik));
	res = lockf(plik, F_ULOCK, 0);
	close(plik);
}

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

