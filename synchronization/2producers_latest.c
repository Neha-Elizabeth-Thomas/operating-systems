#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

#define NIL -125
#define n 4
char buf[n];
sem_t mutex,F,E;

void initialize(){
    for(int i=0 ; i<n ; i++)
        buf[i]=NIL;

    sem_init(&mutex,0,1);
    sem_init(&F,0,0);
    sem_init(&E,0,n);
}

void display(){
    for(int i=0 ; i<n ; i++)
        if(buf[i]==NIL)
            printf(" _ ");
        else if(buf[i]>='a')
            printf("%-4c",buf[i]);
        else
            printf("%-4d",buf[i]);
    printf("\n\n");
}

void* producer(void* arg){
    char item=*((char*)arg);
    int t;
    if(item==0)
        t=1;
    else
        t=2;

    for(int j=0 ; j<26 ; j++){
        sem_wait(&E);
        sem_wait(&mutex);

        for(int i=0 ; i<n ; i++){
            if(buf[i]==NIL){
                buf[i]=item;
                if(item>='a')
                    printf("Put%d: %c  Buffer: ",t,item++);
                else
                    printf("Put%d: %d  Buffer: ",t,item++);
                display();
                sleep(1.5);
                break;
            }
        }
     
        sem_post(&mutex);
        sem_post(&F);
        if(item>'z')
            pthread_exit(NULL);
    }
    pthread_exit(NULL);
}



void* consumer(void* arg){
    while(1){
        sem_wait(&F);
        sem_wait(&mutex);

        for(int i=0 ; i<n ; i++)
            if(buf[i]!=NIL){
                if(buf[i]>='a')
                    printf("Get: %c  Buffer: ",buf[i]);
                else
                    printf("Get: %d  Buffer: ",buf[i]);
                buf[i]=NIL;
                display();
                sleep(2);
                break;
            }

        sem_post(&mutex);
        sem_post(&E);
    }
    pthread_exit(NULL);
}

void main(){

    pthread_t p1,p2,c;
    int num=0;
    char ch='a';
    pthread_attr_t attr;
    initialize();
    pthread_attr_init(&attr);

    pthread_create(&p1,&attr,producer,&num);
    pthread_create(&p2,&attr,producer,&ch);
    pthread_create(&c,&attr,consumer,NULL);

    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    pthread_join(c,NULL);
}
