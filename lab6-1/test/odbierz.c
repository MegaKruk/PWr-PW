#include <stdio.h> 
#include <mqueue.h> 
main(int argc, char *argv[]) { 
     int i, kom, res; 
     unsigned int prior; 
     mqd_t  mq; 
     struct mq_attr attr; 
     /* Utworzenie kolejki komunikatow -----------------*/ 
     attr.mq_msgsize = sizeof(kom); 
     attr.mq_maxmsg = 1; 
     attr.mq_flags = 0; 
     mq=mq_open("/Kolejka", O_RDWR | O_CREAT , 0660, &attr ); 
     res = mq_receive(mq,&kom,sizeof(kom),&prior); 
     printf("Otrzymano komunikat: %d\n",kom); 
     mq_close(mq); 
     mq_unlink("Kolejka"); 
} 
