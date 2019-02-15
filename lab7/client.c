#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define OPENR  1 	// Otwarcie pliku do odczytu 
#define OPENW  2 	// Otwarcie pliku do zapisu 
#define READ   3 	// Odczyt fragmentu pliku 
#define CLOSE  4 	// Zamkniecie pliku 
#define WRITE  5 	// Zapis fragmentu pliku 
#define STOP  10 	// Zatrzymanie serwera 
#define DIR	   6

#define SIZE 512 	// Wielkosc bufora
#define PORT 9950   // PORT
#define SRV_IP "127.0.0.1"

typedef struct  { 
    int  typ;       // typ zlecenia 
    int  ile;   	// liczba bajtow 
    int  fh;        // uchwyt pliku 
    char buf[SIZE]; // bufor 
} mms_t; 

 void blad(char *s) { 
     perror(s); 
     _exit(1); 
 } 

int main(int argc, char* argv[]) {

   struct sockaddr_in adr_moj, adr_serw, adr_x;
   int s, i, slen=sizeof(adr_serw), snd,rec;
   char buf[SIZE];
   mms_t msg;
   msg.ile=sizeof(mms_t);

	s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); 
    if(s < 0) blad("socket"); 
    printf("Gniazdko %d utworzone\n",s); 

    memset((char *) &adr_serw, 0, sizeof(adr_serw)); 
    adr_serw.sin_family = AF_INET; 
    adr_serw.sin_port = htons(PORT); 

    if (inet_aton(argv[1], &adr_serw.sin_addr)==0) { 
    	fprintf(stderr, "inet_aton() failed\n"); 
    	_exit(1); 
	} 

	do {
		printf("\n1 - OPENR\n2 - OPENW\n");
		char temp[1];
		scanf("%s", temp);
		int operacja = temp[0] - '0';
		
		switch(operacja) 
			{

		case OPENR:
			msg.typ = 1;
			strncpy(msg.buf, "client.c", SIZE);
			printf("Wysylam komunikat: %s\n", msg.buf); 
	      		snd = sendto(s, &msg, msg.ile, 0,(struct sockaddr *) &adr_serw, 
	      		(socklen_t) slen); 
	      		if(snd < 0) blad("sendto()"); 
	      		printf("Wyslano komunikat res: %d\n", snd); 
	      		printf("Czekam na odpowiedz\n"); 
	      		rec = recvfrom(s, &msg, msg.ile, 0,(struct sockaddr *) &adr_x, 
	      		(socklen_t *) &slen); 
	      		if(rec < 0) blad("recvfrom()"); 
	      		printf("Otrzymana odpowiedz: %s\n",msg.buf); 
	      		sleep(1);

	      		if(rec >= 0) 
			{
	      			do
				{
		      			msg.typ = 3;
		      			sprintf(msg.buf, "Wysylam komunikat\n"); 
			      		snd = sendto(s, &msg, sizeof(mms_t), 0,(struct sockaddr *) &adr_serw, 
			      		(socklen_t) slen); 
			      		if(snd < 0) blad("sendto()"); 
			      		printf("Wyslano komunikat res: %d\n", snd); 
			      		printf("Czekam na odpowiedz\n"); 
			      		rec = recvfrom(s, &msg, msg.ile, 0,(struct sockaddr *) &adr_x, 
			      		(socklen_t *) &slen); 
			      		if(rec < 0) blad("recvfrom()"); 
			      		printf("Otrzymana odpowiedz: %s\n",msg.buf);
	      			}while(msg.ile == SIZE);

		      		sleep(1);
	      		}
	      		break;

		////////////////
		case OPENW:
			msg.typ = 1;
			strncpy(msg.buf, "text.txt", SIZE);
			msg.fh = open("text.txt",O_RDONLY);
			if(msg.fh<0)
			{ 
			     perror(msg.fh); 
			     _exit(1); 
			} 
			printf("Zapisuje komunikat: %s\n", msg.buf); 
	      		snd = sendto(s, &msg, msg.ile, 0,(struct sockaddr *) &adr_serw, (socklen_t) slen); 
	      		if(snd < 0) blad("sendto()"); 
	      		printf("Zapisano komunikat res: %d\n", snd); 
	      		printf("Czekam na odpowiedz\n"); 
	      		rec = recvfrom(s, &msg, msg.ile, 0,(struct sockaddr *) &adr_x, (socklen_t *) &slen); 
	      		if(rec < 0) blad("recvfrom()"); 
	      		printf("Otrzymana odpowiedz: %s\n",msg.buf); 
	      		sleep(1);

	      		if(rec >= 0) 
			{
	      			do
				{
		      			msg.typ = 5;
		      			sprintf(msg.buf, "Zapisuje komunikat\n"); 
			      		snd = sendto(s, &msg, sizeof(mms_t), 0,(struct sockaddr *) &adr_serw, 
			      		(socklen_t) slen); 
			      		if(snd < 0) blad("sendto()"); 
			      		printf("Zapisano komunikat res: %d\n", snd); 
			      		printf("Czekam na odpowiedz\n"); 
			      		rec = recvfrom(s, &msg, msg.ile, 0,(struct sockaddr *) &adr_x, 
			      		(socklen_t *) &slen); 
			      		if(rec < 0) blad("recvfrom()"); 
			      		printf("Otrzymana odpowiedz: %s\n",msg.buf);
	      			}while(msg.ile == SIZE);

		      		sleep(1);
	      		}

	      		break;
		////////////////////////
	      	
		case 6:
	      		msg.typ = 6;
	      		break;

		}
	}while(1);


	close(s);

	return 0;
}
