#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>

void main(){
    int shmid;
    key_t key=ftok("new.txt",65);
    shmid=shmget(key,1024,0666|IPC_CREAT);

    char *shared_ptr=(char*)shmat(shmid,NULL,0);

    
}
