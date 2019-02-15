#include <stdio.h>
#include <mqueue.h>
#define size 100

struct{
    int typ;
    char text[size];
}kom_t;

void main(int argc, char *argv[]) {
	
    int kom, res,i;
    mqd_t mq;
    unsigned int prior;

    struct mq_attr attr;

    mq=mq_open("/Kolejka", O_RDWR, 0660, NULL );
    if (mq<0)
    {
        perror("Open mq");
        return;
    }

    for(i=0;i<atoi(argv[1]);i++)
    {
        mq_receive(mq,&kom_t,sizeof(kom_t),&prior);
        printf("Odebrano: %s\n",kom_t.text);
    }
   mq_close(mq);

}


