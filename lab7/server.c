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
	
    struct sockaddr_in adr_moj, adr_cli;
    int s, i, slen=sizeof(adr_cli),snd, rec;

	mms_t msg;
	msg.ile=sizeof(mms_t);

	s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(s < 0) blad("socket"); 
    printf("Gniazdko %d utworzone\n",s); 
   
   // Ustalenie adresu IP nadawcy 
   memset((char *) &adr_moj, 0, sizeof(adr_moj)); 
   adr_moj.sin_family = AF_INET; 
   adr_moj.sin_port = htons(PORT); 
   adr_moj.sin_addr.s_addr = htonl(INADDR_ANY); 
   if (bind(s,(struct sockaddr *) &adr_moj, sizeof(adr_moj))==-1) 
       blad("bind");

	do {

		rec = recvfrom(s, &msg, msg.ile, 0, (struct sockaddr *) &adr_cli, &slen);
      	if(rec < 0) blad("recvfrom()"); 
      		printf("Odebrano komunikat z %s:%d res %d\n  Typ: %d %s\n", 
            inet_ntoa(adr_cli.sin_addr), ntohs(adr_cli.sin_port),  
            rec,msg.typ,msg.buf); 
		
		switch(msg.typ) {
			case OPENR:
				msg.fh = open(msg.buf, O_RDONLY, S_IRWXU);
				strncpy(msg.buf, "OK", SIZE);
				break;

			case READ:
				msg.ile = read(msg.fh, msg.buf, SIZE);
				break;

			case OPENW:
				msg.fh = open(msg.buf, O_RDONLY, S_IRWXU);
				strncpy(msg.buf, "OK", SIZE);
				break;

			case WRITE:
				msg.ile = write(msg.fh, msg.buf, msg.ile);
				break;

		}

		// Odpowiedz
		snd = sendto(s, &msg, sizeof(mms_t), 0, (struct sockaddr *) &adr_cli, slen);
		
		if(snd < 0) blad("sendto()"); 
      		printf("wyslano odpowiedz -res %d\n",snd);

	}while(1);

	close(s);

	return 0;
}
