
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>

struct area{
    int S;
    int E;
    int F;
    int num;
};

void wait(int* S){
    while(*S<=0);
    (*S)--;
}

void signal(int* S){ 
    (*S)++;
}

void main(){ 
    int i;
    key_t key=ftok("myfile",987);
    int shmid=shmget(key,sizeof(struct area),0666|IPC_CREAT);
    struct area* shmptr=(struct area*)shmat(shmid,NULL,0);

    for(i=0 ; i<10 ; i++){
        wait(&shmptr->F);
        wait(&shmptr->S);

        printf("GET: %d\n",shmptr->num);

        signal(&shmptr->S);
        signal(&shmptr->E);
    }
    shmdt(shmptr);
    shmctl(shmid,IPC_RMID,NULL);
}
