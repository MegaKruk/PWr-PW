#include <stdio.h>
#include <mqueue.h>
#define size 100

struct{
    int typ;
    char text[size];
} kom_t;

void main(int argc, char *argv[])
{
    int res;
    mqd_t mq;
    struct mq_attr attr;

    attr.mq_msgsize = sizeof(kom_t);
    attr.mq_maxmsg = 2;
    attr.mq_flags = 0;
    mq_unlink("/Kolejka");
    mq=mq_open("/Kolejka", O_RDWR | O_CREAT , 0666, &attr );
    if(mq<0) {
        perror("Kolejka nie została utworzona\n");
    }

    mq_close(mq);
}

