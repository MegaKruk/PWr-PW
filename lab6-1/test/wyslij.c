#include <stdio.h> 
#include <mqueue.h> 
main(int argc, char *argv[]) { 
     int kom, res; 
     mqd_t  mq; 
     struct mq_attr attr; 
     /* Utworzenie kolejki komunikatow -----------------*/ 
     attr.mq_msgsize = sizeof(kom); 
     attr.mq_maxmsg = 1; 
     attr.mq_flags = 0; 
     mq=mq_open("/Kolejka", O_RDWR | O_CREAT , 0660, &attr ); 
     kom = atoi(argv[1]); 
     res = mq_send(mq,&kom,sizeof(kom),10); 
     printf("Wyslano komunikat: %d\n",kom); 
     mq_close(mq); 
     mq_unlink("Kolejka"); 
}    
