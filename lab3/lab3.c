#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
// #include "process.h"

// 1 wez poczatek i koniec zakresy
// 2 wez ilosc ilementow (odejmij) - zakres (min 1 mil)
// 3 podziel przez 4 - podzakres
// kazdy proces dostaje czesc zakresu o indeksach i * podzakres

int main(int argc, char * argv[])
{ 
	int pid, i, status, lp, l, x, y, d, counter, p; 
	int suma = 0;
	unsigned long long k, j;
	//char kroki[80]; 
	
	//lp = argc - 2;
	//printf("Instrukcja wspolna\n");
	unsigned long long pocz = atoi(argv[1]);
	unsigned long long koniec = atoi(argv[2]);
	unsigned long long proc =  atoi(argv[3]);

	unsigned long long zakres = koniec - pocz;
	unsigned long long podzakres = zakres/proc;
	
	unsigned long long begin = pocz;
	unsigned long long end = pocz + podzakres;
	
	unsigned long long zbior[100] = {0};
	unsigned long long wyniki[100] = {0};
	unsigned long long wynikiproc[100] = {0};

	int sekundy1, sekundy2, czas;

	
int pierwsza(int n)
{
 for(p=2; p*p<=n;p++)
 {
 if(n%i == 0) return 0;
 }
 return 1;
}
	for(int z = 0; z < proc; z++)
	{
		zbior[z] = z * podzakres;
	}
	
	sekundy1 = time(NULL);

	for(i = 0; i < proc; i++) 
	{
		if((pid = fork()) == 0) 
		{
			//tutaj licz
			/*for(j = begin; j <= end; j++)
			{
				counter = 0;
				for(y = 1; y <= j; y++)
				{
					if(y%j == 0 && y != 1)
						counter++;
				}
				if(counter == 0)
				{
					wyniki[i]++;
				}*/
				printf("\nproces %d liczy od liczby %d\n", i, begin);
				counter = 0;
				for(j = begin; j <= end; j++)
				{
				wyniki[i] += pierwsza(j);
				}
                	        
                	        exit(wyniki[i]);  
		         
/*
int pierwsza(int n) 
// Funkcja zwraca 1 gdy n jest liczbą
 pierwsza 0 gdy nie                                   
{ int i,j=0; 
  for(i=2;i*i<=n;i++) { 
    if(n%i == 0) return(0) ; 
 } 
 return(1); 
}   */	
		}
		begin = end + 1;
		end = end + podzakres - 2;
	}	

	// tutaj wynik
	
	for(int l = 0; l < proc; l++)
	{
		pid = wait(&status);
		wynikiproc[l] = status/256;
		//printf("Proces %d zakończony, status %d\n", pid,WEXITSTATUS(status)); 
	}

	sekundy2 = time(NULL);
	czas = sekundy2 - sekundy1;

	for(int d = 0; d < proc; d++)
	{
		suma += wynikiproc[d];
	}
	printf("\nIlosc %d\tczas %d\n", suma, czas);
	exit(0);
	return 0; 
}
