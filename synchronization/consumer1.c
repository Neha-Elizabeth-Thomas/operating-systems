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
    shmid=shmget(key,sizeof(struct area),0666);
    shmptr=(struct area*)shmat(shmid,NULL,0);

    for(int j=0 ; j<10 ; j++){
        sem_wait(&(shmptr->F));
        sem_wait(&(shmptr->mutex));

        for(int i=0 ; i<n ; i++)
            if(shmptr->buf[i]!=NIL){
                printf("Get: %d  Buffer: ",shmptr->buf[i]);
                shmptr->buf[i]=NIL;
                display(shmptr);
                sleep(1);
                break;
            }

        sem_post(&(shmptr->mutex));
        sem_post(&(shmptr->E));
    }
    shmdt(&shmptr);
    shmctl(shmid,IPC_RMID,NULL);
 }
