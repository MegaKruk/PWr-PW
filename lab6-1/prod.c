#include <stdio.h>
#include <mqueue.h>
#define size 100

void main(int argc, char *argv[]) {

struct{
    int typ;
    char text[size];
}kom_t;
    int kom, res, i,j;
    mqd_t mq;

    mq=mq_open("/Kolejka", O_RDWR, 0660,NULL );
    if (mq<0)
    {
        perror("Open mq");
        return;
    }

    for(j=0;j<atoi(argv[2]);j++)
    {
        sprintf(kom_t.text, "Producent %s krok: %d",argv[1],j+1);
        printf("%s\n",kom_t.text);
        mq_send(mq,&kom_t,sizeof(kom_t),10);
        sleep(1);
    }

    mq_close(mq);
    //printf("prod koniec\n");
}

