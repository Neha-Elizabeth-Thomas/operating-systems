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

    shmptr->S=1;
    shmptr->E=1;
    shmptr->F=0;

    for(i=0 ; i<10 ; i++){
        wait(&shmptr->E);
        wait(&shmptr->S);

        srand(time(0));
        shmptr->num=rand()%1000;
        printf("PUT: %d\n",shmptr->num);
        sleep(2);

        signal(&shmptr->S);
        signal(&shmptr->F);
    }
    shmdt(shmptr);
}
