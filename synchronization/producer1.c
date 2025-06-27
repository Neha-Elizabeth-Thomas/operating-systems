#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<semaphore.h>
#define n 4
#define NIL -999

struct area{
    int buf[n];
    sem_t mutex;
    sem_t E;
    sem_t F;
};

void initialize(struct area* shmptr){
    for(int i=0 ; i<n ; i++)
        shmptr->buf[i]=NIL;

    sem_init(&(shmptr->mutex),1,1);
    sem_init(&(shmptr->F),1,0);
    sem_init(&(shmptr->E),1,n);
}

void display(struct area* shmptr){
    for(int i=0 ; i<n ; i++)
        if(shmptr->buf[i]==NIL)
            printf(" _ ");
        else
            printf("%-5d",shmptr->buf[i]);
    printf("\n\n");
}

void main(){
    int shmid;
    struct area* shmptr;
    key_t key=ftok("myfile.txt",321);
    shmid=shmget(key,sizeof(struct area),IPC_CREAT|0666);
    shmptr=(struct area*)shmat(shmid,NULL,0);
    
    initialize(shmptr);

    for(int j=0 ; j<10 ; j++){
        sem_wait(&(shmptr->E));
        sem_wait(&(shmptr->mutex));

        srand(time(0));
        for(int i=0 ; i<n ; i++)
            if(shmptr->buf[i]==NIL){
               shmptr->buf[i]=rand()%100;
                printf("Put: %d  Buffer: ",shmptr->buf[i]) ;
                display(shmptr);
                sleep(1);
                break;
            }

        sem_post(&(shmptr->mutex));
        sem_post(&(shmptr->F));
    }
    shmdt(shmptr);
}


