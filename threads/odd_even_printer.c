#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
int available=1;

void acquire(){
    while(!available);
    available=0;
}

void release(){
    available=1;
}

int turn,flag[2];

void* display(void * arg){
    int* start=(int*)arg;
    int temp=*start;
    while(1){
        turn=1-*start;
        flag[*start]=1;
        while(turn==1-*start && flag[1-*start]);
        acquire();

        printf("From  thread%d: %d\n\n",*start,temp);
        temp+=2;
        sleep(1);

        flag[*start]=0;
        release();
    }
    
    return NULL;
}

void main(){
    pthread_t odd,even;
    int num1=0,num2=1;
    pthread_create(&even,NULL,display,&num1);
    pthread_create(&odd,NULL,display,&num2);

    pthread_join(odd,NULL); 
    pthread_join(even,NULL);
}
