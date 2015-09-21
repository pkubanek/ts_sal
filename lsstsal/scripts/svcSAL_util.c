#include <time.h>

int svcSAL_sleep(unsigned long milisec)  
{  
     struct timespec req={0};  
     time_t sec=(int)(milisec/1000);  
     milisec=milisec-(sec*1000);  
     req.tv_sec=sec;  
     req.tv_nsec=milisec*1000000L;  
     while(nanosleep(&req,&req)==-1)  
       continue;  
     return 1;  
}


int svcSAL_nsleep(unsigned long nanosec)  
{  
     struct timespec req={0};  
     time_t sec=0;  
     req.tv_sec=sec;  
     req.tv_nsec=nanosec;  
     while(nanosleep(&req,&req)==-1)  
       continue;  
     return 1;  
}


 
